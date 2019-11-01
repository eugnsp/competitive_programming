/*********************************************************************
ACM contest and blackout
------------------------
UVa ID: 106 00

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <numeric>
#include <utility>
#include <vector>

using Size = unsigned int;
using Weight = unsigned int;
using Adjacency_list = std::vector<std::vector<std::pair<Size, Weight>>>;

class Disjoint_sets
{
public:
	// Creates a disjoint set of (n) disjoint elements
	Disjoint_sets(Size n)
	{
		sizes_.assign(n, 1);
		parents_.resize(n);
		std::iota(parents_.begin(), parents_.end(), static_cast<Size>(0));
	}

	// Unites two elements and returns the size of the new set
	Size unite(Size x, Size y)
	{
		auto px = find_parent(x);
		auto py = find_parent(y);
		assert(px != py);

		if (sizes_[py] < sizes_[px])
			std::swap(px, py);

		parents_[px] = py;
		sizes_[py] += sizes_[px];

		return sizes_[py];
	}

	bool is_same_set(Size x, Size y) const
	{
		return find_parent(x) == find_parent(y);
	}

private:
	Size find_parent(Size x) const
	{
		auto& parent = parents_[x];
		if (parent != x)
			parent = find_parent(parent);

		return parent;
	}

private:
	std::vector<Size> sizes_;
	mutable std::vector<Size> parents_;
};

struct Edge
{
	Size vertex1;
	Size vertex2;
	Weight weight;

	bool operator<(const Edge& other) const
	{
		return weight < other.weight;
	}
};

// Returns the minimum spanning tree using the Kruskal's algorithm
Adjacency_list min_span_tree(Size n_vertices, const std::vector<Edge>& graph)
{
	Adjacency_list mst(n_vertices);
	Disjoint_sets ds(n_vertices);

	auto gr = graph;
	std::sort(gr.begin(), gr.end());

	for (const auto& edge : gr)
		if (!ds.is_same_set(edge.vertex1, edge.vertex2))
		{
			mst[edge.vertex1].push_back({edge.vertex2, edge.weight});
			mst[edge.vertex2].push_back({edge.vertex1, edge.weight});
			if (ds.unite(edge.vertex1, edge.vertex2) == n_vertices)
				break;
		}

	return mst;
}

bool contains_edge(const Adjacency_list& graph, const Edge& edge)
{
	auto& succs = graph[edge.vertex1];
	const auto succ = std::find_if(
		succs.begin(), succs.end(), [&edge](auto& e) { return e.first == edge.vertex2; });

	return succ != succs.end();
}

bool weights_along_path(const Adjacency_list& graph, std::vector<Weight>& weights,
						Size vertex, Size parent, Size last)
{
	constexpr bool vertex_found = true;

	if (vertex == last)
		return vertex_found;

	for (auto succ : graph[vertex])
		if (succ.first != parent)
		{
			weights.push_back(succ.second);
			if (weights_along_path(graph, weights, succ.first, vertex, last) == vertex_found)
				return vertex_found;

			weights.pop_back();
		}

	return !vertex_found;
}

// Returns the maximum weight of edges connecting vertices (first) and (last)
Weight max_weight_along_path(const Adjacency_list& graph, Size first, Size last)
{
	std::vector<Weight> weights;
	weights_along_path(graph, weights, first, first, last);

	assert(!weights.empty());
	return *std::max_element(weights.begin(), weights.end());
}

// Returns the weights of the first and second minimum spanning trees
std::pair<Weight, Weight> min_span_tree_weight_1_2(Size n_vertices, const std::vector<Edge>& graph)
{
	auto mst = min_span_tree(n_vertices, graph);

	Weight min_weight = 0;
	Weight min_diff = static_cast<Weight>(-1);

	for (auto& edge : graph)
		if (contains_edge(mst, edge))
			min_weight += edge.weight;
		else
		{
			auto deleted_weight = max_weight_along_path(mst, edge.vertex1, edge.vertex2);
			assert(edge.weight >= deleted_weight);
			auto diff = edge.weight - deleted_weight;
			min_diff = std::min(min_diff, diff);
		}

	return {min_weight, min_weight + min_diff};
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(n_schools_);
		assert(3 < n_schools_ && n_schools_ < 100);

		std::size_t n_connections;
		read(n_connections);

		connections_.clear();
		connections_.reserve(n_connections);
		for (std::size_t i = 0; i < n_connections; ++i)
		{
			Edge edge;
			read(edge.vertex1, edge.vertex2, edge.weight);
			--edge.vertex1; // To zero-based indexing
			--edge.vertex2;
			connections_.push_back(edge);
		}
	}

	virtual void solve(unsigned int) override
	{
		const auto costs = min_span_tree_weight_1_2(n_schools_, connections_);
		write_ln(costs.first, costs.second);
	}

private:
	Size n_schools_;
	std::vector<Edge> connections_;
};

MAIN

/*********************************************************************
Internet bandwidth
------------------
UVa ID: 008 20

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using Flow = unsigned int;
using Size = unsigned int;
constexpr auto unvisited_vertex = static_cast<Size>(-1);

struct Edge
{
	Size to;
	Flow flow;
};

using Adjacency_list = std::vector<std::vector<Edge>>;

class Graph
{
public:
	Graph(const Adjacency_list& graph)
	{
		const auto n_vertices = graph.size();
		edge_indices_.resize(n_vertices);
		Size edge_index = 0;

		for (Size v = 0; v < n_vertices; ++v)
			for (auto& edge : graph[v])
			{
				edges_.push_back({edge.to, edge.flow});
				edges_.push_back({v, edge.flow});

				edge_indices_[v].push_back(edge_index++);
				edge_indices_[edge.to].push_back(edge_index++);
			}
	}

	Size vertices() const
	{
		return static_cast<Size>(edge_indices_.size());
	}

	const std::vector<Size>& edges(Size vertex) const
	{
		return edge_indices_[vertex];
	}

	Edge& edge(Size index)
	{
		return edges_[index];
	}

	const Edge& edge(Size index) const
	{
		return edges_[index];
	}

	Edge& opposite_edge(Size index)
	{
		const auto opposite_index = index ^ 1;
		return edges_[opposite_index];
	}

private:
	// Indices of the outgoing edges in the (edges) array
	std::vector<std::vector<Size>> edge_indices_;

	// An edge and its opposite edge are stored as consecutive pairs,
	// i.e. the opposite edge index is given by (edge_index ^ 1)
	std::vector<Edge> edges_;
};

std::vector<Size> bfs_augmenting_path(const Graph& graph, Size source, Size dest)
{
	// After search, (pred[vertex]) contains a pair of the previous vertex and edge indices,
	// this array is also used to skip visited vertices
	std::vector<std::pair<Size, Size>> pred(graph.vertices(), {unvisited_vertex, 0});

	std::queue<Size> queue;
	queue.push(source);

	while (!queue.empty())
	{
		const auto v = queue.front();
		queue.pop();

		if (v == dest)
			break;

		for (auto edge_index : graph.edges(v))
		{
			auto& edge = graph.edge(edge_index);
			if (edge.flow > 0 && pred[edge.to].first == unvisited_vertex)
			{
				pred[edge.to] = {v, edge_index};
				queue.push(edge.to);
			}
		}
	}

	std::vector<Size> edges;
	if (pred[dest].first != unvisited_vertex)
	{
		// Recover the path
		edges.push_back(pred[dest].second);
		while (pred[dest].first != source)
		{
			dest = pred[dest].first;
			edges.push_back(pred[dest].second);
		}
	}

	return edges;
}

// Returns the maximum network flow in the (graph) from (source) to (dest)
// using the Edmonds-Karp's algorithm
Flow max_network_flow(const Adjacency_list& graph, Size source, Size dest)
{
	Graph res_graph(graph);

	Flow max_flow = 0;
	while (true)
	{
		const auto path = bfs_augmenting_path(res_graph, source, dest);
		if (path.empty())
			break;

		// Find maximum possible flow along the (path)
		Flow d_flow = std::numeric_limits<Flow>::max();
		for (auto edge_index : path)
		{
			assert(res_graph.edge(edge_index).flow > 0);
			d_flow = std::min(d_flow, res_graph.edge(edge_index).flow);
		}

		// Update the edges
		for (auto edge_index : path)
		{
			res_graph.edge(edge_index).flow -= d_flow;
			res_graph.opposite_edge(edge_index).flow += d_flow;
		}

		max_flow += d_flow;
	}

	return max_flow;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		Size n_nodes;
		if (!read(n_nodes) || n_nodes == 0)
			return false;

		assert(2 <= n_nodes && n_nodes <= 100);
		network_.clear();
		network_.resize(n_nodes);

		Size n_connections;
		read(source_, dest_, n_connections);
		--source_, --dest_; // To zero-based indexing
		assert(source_ < n_nodes && dest_ < n_nodes);

		for (Size i = 0; i < n_connections; ++i)
		{
			Size n1, n2;
			Flow bandwidth;
			read(n1, n2, bandwidth);
			--n1, --n2; // To zero-based indexing
			network_[n1].push_back({n2, bandwidth});
		}

		return true;
	}

	virtual void solve(unsigned int i_case) override
	{
		write_ln("Network ", i_case + 1);
		write_ln("The bandwidth is ", max_network_flow(network_, source_, dest_), '.');
		write_ln();
	}

private:
	Size source_, dest_;
	Adjacency_list network_;
};

MAIN(CP)

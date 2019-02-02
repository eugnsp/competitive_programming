/*********************************************************************
Commandos
---------
UVa ID: 114 63

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <limits>
#include <vector>

using Dist = unsigned int;
using Adjacency_list = std::vector<std::vector<std::size_t>>;

// Returns a matrix of all-pairs shortest paths using
// the Floyd-Warshall algorithm
Matrix<Dist> all_pairs_shortest_paths(const Adjacency_list& graph)
{
	constexpr auto infinite_dist = std::numeric_limits<Dist>::max();

	const auto n_vertices = graph.size();
	Matrix<Dist> dist(n_vertices, n_vertices, infinite_dist);

	for (std::size_t vertex = 0; vertex < n_vertices; ++vertex)
	{
		dist(vertex, vertex) = 0;
		for (auto succ : graph[vertex])
			dist(vertex, succ) = dist(succ, vertex) = 1;
	}

	for (std::size_t k = 0; k < n_vertices; ++k)
		for (std::size_t i = 0; i < n_vertices; ++i)
			for (std::size_t j = 0; j < n_vertices; ++j)
				if (dist(i, k) != infinite_dist && dist(k, j) != infinite_dist)
					dist(i, j) = std::min(dist(i, j), dist(i, k) + dist(k, j));

	return dist;
}

Dist max_source_x_dest_dist(const Adjacency_list& graph, std::size_t source, std::size_t dest)
{
	const auto dist = all_pairs_shortest_paths(graph);

	Dist max_dist = 0;
	for (std::size_t vertex = 0; vertex < graph.size(); ++vertex)
		max_dist = std::max(max_dist, dist(source, vertex) + dist(vertex, dest));

	return max_dist;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t n_buildings, n_roads;

		read(n_buildings, n_roads);
		assert(n_buildings <= 100);

		graph_.clear();
		graph_.resize(n_buildings);
		for (std::size_t i = 0; i < n_roads; ++i)
		{
			std::size_t from, to;
			read(from, to);
			graph_[from].push_back(to);
		}

		read(source_, dest_);
	}

	virtual void solve(unsigned int i_case) override
	{
		write_ln("Case ", i_case + 1, ": ", max_source_x_dest_dist(graph_, source_, dest_));
	}

private:
	Adjacency_list graph_;
	std::size_t source_, dest_;
};

MAIN(CP)

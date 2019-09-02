/*********************************************************************
Ordering tasks
--------------
UVa ID: 103 05

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

using Size = unsigned int;
using Vertex_list = std::vector<Size>;
using Adjacency_list = std::vector<Vertex_list>;

void topologic_sort_impl(const Adjacency_list& graph, std::vector<bool>& visited, Size vertex, Vertex_list& sorted)
{
	assert(!visited[vertex]);
	visited[vertex] = true;

	for (auto succ : graph[vertex])
		if (!visited[succ])
			topologic_sort_impl(graph, visited, succ, sorted);

	sorted.push_back(vertex);
}

// Returns the list of topologically sorted vertices in the (graph)
// (the DFS is used)
Vertex_list topologic_sort(const Adjacency_list& graph)
{
	Vertex_list sorted_vertices;
	std::vector<bool> visited(graph.size(), false);

	for (Size vertex = 0; vertex < graph.size(); ++vertex)
		if (!visited[vertex])
			topologic_sort_impl(graph, visited, vertex, sorted_vertices);

	std::reverse(sorted_vertices.begin(), sorted_vertices.end());
	return sorted_vertices;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		if (!read(n_tasks_) || n_tasks_ == 0)
			return false;

		Size n_precedences;
		read(n_precedences);

		precedences_.clear();
		precedences_.resize(n_tasks_);
		for (Size i = 0; i < n_precedences; ++i)
		{
			Size t1, t2;
			read(t1, t2);
			--t1, --t2; // To zero-based indexing
			precedences_[t1].push_back(t2);
		}

		return true;
	}

	virtual void solve(unsigned int) override
	{
		const auto order = topologic_sort(precedences_);
		write_vec(
			order, [](Size index) { return index + 1; }, ' '); // To one-based indexing
		write_ln();
	}

private:
	Size n_tasks_;
	Adjacency_list precedences_;
};

MAIN


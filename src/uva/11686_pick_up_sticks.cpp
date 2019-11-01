/*********************************************************************
Pick up sticks
--------------
UVa ID: 116 86

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <vector>

using Size = unsigned int;
using Vertex_list = std::vector<Size>;
using Adjacency_list = std::vector<Vertex_list>;

enum class Status
{
	UNVISITED,
	DISCOVERED,
	VISITED
};

void topologic_sort_impl(const Adjacency_list& graph,
						 std::vector<Status>& statuses,
						 Size vertex, Vertex_list& sorted)
{
	auto& st = statuses[vertex];
	assert(st == Status::UNVISITED);

	st = Status::DISCOVERED;
	for (auto succ : graph[vertex])
	{
		const auto& succ_st = statuses[succ];
		if (succ_st == Status::DISCOVERED) // Cycle is detected
			return;						   // without setting VISITED status, signifying an error
		else if (succ_st == Status::UNVISITED)
		{
			topologic_sort_impl(graph, statuses, succ, sorted);
			if (succ_st != Status::VISITED)
				return;
		}
	}

	st = Status::VISITED;
	sorted.push_back(vertex);
}

// Returns the list of topologically sorted vertices in the (graph)
Vertex_list topologic_sort(const Adjacency_list& graph)
{
	Vertex_list sorted_vertices;
	std::vector<Status> statuses(graph.size(), Status::UNVISITED);

	sorted_vertices.reserve(graph.size());
	for (Size vertex = 0; vertex < graph.size(); ++vertex)
		if (statuses[vertex] == Status::UNVISITED)
		{
			topologic_sort_impl(graph, statuses, vertex, sorted_vertices);
			if (statuses[vertex] != Status::VISITED)
			{
				sorted_vertices.clear();
				break;
			}
		}

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
		if (!order.empty())
			for (auto it = order.rbegin(); it != order.rend(); ++it)
				write_ln(*it + 1); // To one-based indexing
		else
			write_ln("IMPOSSIBLE");
	}

private:
	Size n_tasks_;
	Adjacency_list precedences_;
};

MAIN

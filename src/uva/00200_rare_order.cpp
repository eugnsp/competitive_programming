/*********************************************************************
Rare order
----------
UVa ID: 002 00

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <string>
#include <set>
#include <vector>

using Size = unsigned int;
using Vertex_list = std::vector<Size>;
using Adjacency_list = std::vector<std::set<Size>>;

void topologic_sort_impl(
	const Adjacency_list& graph, std::vector<bool>& visited, Size vertex, Vertex_list& sorted)
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
Vertex_list topologic_sort(const Adjacency_list& graph, std::vector<bool> visited)
{
	assert(graph.size() == visited.size());
	Vertex_list sorted_vertices;

	for (Size vertex = 0; vertex < graph.size(); ++vertex)
		if (!visited[vertex])
			topologic_sort_impl(graph, visited, vertex, sorted_vertices);

	return sorted_vertices;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::string str, prev;

		precedences_.assign(26, {});
		unseen_letters_.assign(26, true);

		while (true)
		{
			if (!read_ln(str))
				return false;
			if (str == "#")
				break;

			unseen_letters_[index(str.front())] = false;

			auto it = str.cbegin();
			auto it_prev = prev.cbegin();
			while (it != str.cend() && it_prev != prev.cend() && *it == *it_prev)
				++it, ++it_prev;

			if (it != str.cend() && it_prev != prev.cend())
			{
				precedences_[index(*it_prev)].insert(index(*it));
				unseen_letters_[index(*it)] = false;
				unseen_letters_[index(*it_prev)] = false;
			}

			std::swap(str, prev);
		}

		return true;
	}

	virtual void solve(unsigned int) override
	{
		const auto order = topologic_sort(precedences_, unseen_letters_);
		for (auto it = order.rbegin(); it != order.rend(); ++it)
			write(letter(*it));
		write_ln();
	}

	static Size index(char ch)
	{
		assert('A' <= ch && ch <= 'Z');
		return static_cast<Size>(ch - 'A');
	}

	static char letter(Size index)
	{
		assert(index < 26);
		return static_cast<char>('A' + index);
	}

private:
	Size n_tasks_;
	Adjacency_list precedences_;
	std::vector<bool> unseen_letters_;
};

MAIN(CP)

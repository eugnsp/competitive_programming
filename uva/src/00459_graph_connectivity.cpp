/*********************************************************************
Graph connectivity
------------------
UVa ID: 004 59

Consider a graph G formed from a large number of nodes connected by
edges. G is said to be connected if a path can be found in 0 or more
steps between any pair of nodes in G. A connected subgraph is maximal
if there are no nodes and edges in the original graph that could be
added to the subgraph and still leave it connected. Write a program to
determine the number of maximal connected sub-graphs of a given graph.

Input
-----
The input begins with a single positive integer on a line by itself
indicating the number of the cases following, each of them as described
below. This line is followed by a blank line, and there is also a blank
line between two consecutive inputs. The first line of each input set
contains a single uppercase alphabetic character. This character
represents the largest node name in the graph. Each successive line
contains a pair of uppercase alphabetic characters denoting an edge
in the graph. The sample input section contains a possible input set
for the graph pictured above. Input is terminated by a blank line.

Output
------
For each test case, write in the output the number of maximal connected
subgraphs. The outputs of two consecutive cases will be separated by
a blank line.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <string>
#include <vector>
#include <utility>

template<typename T>
class Disjoint_sets
{
public:
	template<class It>
	Disjoint_sets(It first, const It last)
	{
		nodes_.resize(static_cast<std::size_t>(last - first));
		for (auto node = nodes_.begin(); first != last; ++first, ++node)
		{
			node->value = *first;
			node->parent = node;
		}
	}

	void unite(const T& x, const T& y)
	{
		const auto root_x = find_root(pos(x));
		const auto root_y = find_root(pos(y));
		if (root_x != root_y)
			root_y->parent = root_x;
	}

	std::size_t count() const
	{
		std::size_t n = 0;
		for (auto node = nodes_.begin(); node != nodes_.end(); ++node)
			if (node->parent == node)
				++n;
		return n;
	}

private:
	struct Node;
	using Iter = typename std::vector<Node>::iterator;

	struct Node
	{
		T value;
		Iter parent;
	};

	Iter pos(const T& x)
	{
		const auto pos = std::find_if(nodes_.begin(), nodes_.end(),
			[&x](const Node& node) { return node.value == x; });

		assert(pos != nodes_.end());
		return pos;
	}

	Iter find_root(const Iter pos)
	{
		if (pos->parent != pos)
			pos->parent = find_root(pos->parent);

		return pos->parent;
	}

private:
	std::vector<Node> nodes_;
};

using Vertex_index = unsigned char;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_ln(max_vertex_index_);

		edges_.clear();
		for (std::string edge; read_ln(edge);)
		{
			assert(edge.length() == 2);
			edges_.push_back({edge[0], edge[1]});
		}
	}

	virtual void solve(unsigned int i_case) override
	{
		const auto n_vertices = static_cast<std::size_t>(max_vertex_index_ - 'A') + 1;
		std::vector<Vertex_index> vertices(n_vertices);
		std::iota(vertices.begin(), vertices.end(), 'A');

		Disjoint_sets<Vertex_index> disjoint_sets(vertices.begin(), vertices.end());
		for (const auto& edge : edges_)
			disjoint_sets.unite(edge.first, edge.second);

		if (i_case > 1)
			write_ln();
		write_ln(disjoint_sets.count());
	}

private:
	using Edge = std::pair<Vertex_index, Vertex_index>;

	Vertex_index max_vertex_index_;
	std::vector<Edge> edges_;
};

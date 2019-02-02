/*********************************************************************
Graph connectivity
------------------
UVa ID: 004 59

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <string>
#include <vector>
#include <utility>

using Vertex_index = unsigned char;

class Disjoint_sets
{
private:
	struct Node
	{
		Vertex_index value;
		std::vector<Node>::iterator parent;
	};

	using Nodes = std::vector<Node>;

public:
	Disjoint_sets(const std::vector<Vertex_index>& elements)
	{
		nodes_.resize(elements.size());
		for (auto node = nodes_.begin(); node != nodes_.end(); ++node)
		{
			node->value = elements[node - nodes_.begin()];
			node->parent = node;
		}
	}

	void unite(Vertex_index x, Vertex_index y)
	{
		const auto root_x = find_root(pos(x));
		const auto root_y = find_root(pos(y));
		if (root_x != root_y)
			root_y->parent = root_x;
	}

	std::size_t n_sets() const
	{
		std::size_t n = 0;
		for (auto node = nodes_.begin(); node != nodes_.end(); ++node)
			if (node->parent == node)
				++n;
		return n;
	}

private:
	Nodes::iterator pos(Vertex_index x)
	{
		const auto pos = std::find_if(
			nodes_.begin(), nodes_.end(), [&x](const Node& node) { return node.value == x; });

		assert(pos != nodes_.end());
		return pos;
	}

	Nodes::iterator find_root(Nodes::iterator pos)
	{
		if (pos->parent != pos)
			pos->parent = find_root(pos->parent);

		return pos->parent;
	}

private:
	Nodes nodes_;
};

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_ln(max_vertex_index_);
		assert(between(max_vertex_index_, 'A', 'Z'));

		std::string edge;

		edges_.clear();
		while (read_ln(edge))
		{
			assert(edge.length() == 2);
			assert(
				between(edge[0], 'A', max_vertex_index_) &&
				between(edge[1], 'A', max_vertex_index_));
			edges_.push_back({edge[0], edge[1]});
		}
	}

	virtual void solve(unsigned int i_case) override
	{
		std::vector<Vertex_index> vertices(max_vertex_index_ - 'A' + 1);
		std::iota(vertices.begin(), vertices.end(), 'A');

		Disjoint_sets disjoint_sets(vertices);
		for (const auto& edge : edges_)
			disjoint_sets.unite(edge.first, edge.second);

		if (i_case > 0)
			write_ln();
		write_ln(disjoint_sets.n_sets());
	}

private:
	Vertex_index max_vertex_index_;
	std::vector<std::pair<Vertex_index, Vertex_index>> edges_;
};

MAIN(CP)

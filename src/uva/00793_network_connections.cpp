/*********************************************************************
Network connections
-------------------
UVa ID: 007 93

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <string>
#include <sstream>
#include <vector>

using Index = unsigned int;

enum class Type
{
	CONNECT,
	QUERY
};

struct Log
{
	Type type;
	Index computer1;
	Index computer2;
};

class Disjoint_sets
{
private:
	struct Node
	{
		Index value;
		std::vector<Node>::iterator parent;
	};

	using Nodes = std::vector<Node>;

public:
	Disjoint_sets(const std::vector<Index>& elements)
	{
		nodes_.resize(elements.size());
		for (auto node = nodes_.begin(); node != nodes_.end(); ++node)
		{
			node->value = elements[node - nodes_.begin()];
			node->parent = node;
		}
	}

	void unite(Index x, Index y)
	{
		const auto root_x = find_root(pos(x));
		const auto root_y = find_root(pos(y));
		if (root_x != root_y)
			root_y->parent = root_x;
	}

	bool is_same_set(Index x, Index y)
	{
		const auto root_x = find_root(pos(x));
		const auto root_y = find_root(pos(y));
		return (root_x == root_y);
	}

private:
	Nodes::iterator pos(Index x)
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
		read_ln(n_computers_);

		std::string line_str;

		log_lines_.clear();
		while (read_ln(line_str))
		{
			std::istringstream line(line_str);
			char type;
			Index computer1, computer2;
			line >> type >> computer1 >> computer2;

			--computer1, --computer2; // To zero-based indexing
			log_lines_.push_back({type == 'c' ? Type::CONNECT : Type::QUERY, computer1, computer2});
		}
	}

	virtual void solve(unsigned int i_case) override
	{
		std::vector<Index> computers(n_computers_);
		std::iota(computers.begin(), computers.end(), static_cast<Index>(0));

		std::size_t n_successful = 0;
		std::size_t n_unsuccessful = 0;

		Disjoint_sets network(computers);
		for (const auto& line : log_lines_)
		{
			if (line.type == Type::CONNECT)
				network.unite(line.computer1, line.computer2);
			else
				network.is_same_set(line.computer1, line.computer2) ? ++n_successful
																	: ++n_unsuccessful;
		}

		if (i_case > 0)
			write_ln();
		write_ln(n_successful, ',', n_unsuccessful);
	}

private:
	Index n_computers_;
	std::vector<Log> log_lines_;
};



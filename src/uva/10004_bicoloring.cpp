/*********************************************************************
Bicoloring
----------
UVa ID: 100 04

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <queue>
#include <vector>

using Size = unsigned int;
using Vertex_list = std::vector<Size>;
using Adjacency_list = std::vector<Vertex_list>;

bool is_bicolorable(const Adjacency_list& graph)
{
	enum Color
	{
		UNDEFINED,
		RED,
		BLACK
	};

	std::vector<Color> colors(graph.size(), UNDEFINED);
	std::queue<Size> queue;

	colors[0] = RED;
	queue.push(0);

	while (!queue.empty())
	{
		const auto v = queue.front();
		queue.pop();

		assert(colors[v] != UNDEFINED);

		const auto succ_color = (colors[v] == RED) ? BLACK : RED;
		for (auto succ : graph[v])
			if (colors[succ] == UNDEFINED)
			{
				colors[succ] = succ_color;
				queue.push(succ);
			}
			else if (colors[succ] == colors[v])
				return false;
	}

	return true;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		Size n_nodes;
		if (!read(n_nodes) || n_nodes == 0)
			return false;

		Size n_edges;
		read(n_edges);

		graph_.clear();
		graph_.resize(n_nodes);

		for (Size e = 0; e < n_edges; ++e)
		{
			Size n1, n2;
			read(n1, n2);
			graph_[n1].push_back(n2);
			graph_[n2].push_back(n1);
		}

		return true;
	}

	virtual void solve(unsigned int) override
	{
		if (!is_bicolorable(graph_))
			write("NOT ");
		write_ln("BICOLORABLE.");
	}

private:
	Adjacency_list graph_;
};

int main()
{
	CP p;
	return p.run();
}

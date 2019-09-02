/*********************************************************************
Wormholes
---------
UVa ID: 005 58

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

using Weight = int;
using Size = unsigned int;
using Edge = std::pair<Size, Weight>;
using Adjacency_list = std::vector<std::vector<Edge>>;

// Checks whether the graph has a negative cycle reachable from
// the vertex (start) using the Bellman-Ford algorithm
bool has_negative_cycle(const Adjacency_list& graph, Size start)
{
	constexpr auto max_weight = std::numeric_limits<Weight>::max();
	std::vector<Weight> distances(graph.size(), max_weight);
	distances[start] = 0;

	for (Size i = 1; i < graph.size(); ++i)
	{
		bool relaxed = false;
		for (Size vertex = 0; vertex < graph.size(); ++vertex)
			for (auto& edge : graph[vertex])
				if (distances[vertex] < max_weight)
				{
					const auto new_dist = distances[vertex] + edge.second;
					if (new_dist < distances[edge.first])
					{
						distances[edge.first] = new_dist;
						relaxed = true;
					}
				}

		if (!relaxed)
			return false;
	}

	for (Size vertex = 0; vertex < graph.size(); ++vertex)
		for (auto& edge : graph[vertex])
			if (distances[edge.first] - edge.second > distances[vertex])
				return true;

	return false;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		Size n_wormholes_;
		read(n_stars_, n_wormholes_);

		assert(1 <= n_stars_ && n_stars_ <= 1000);
		assert(n_wormholes_ <= 2000);

		wormholes_.clear();
		wormholes_.resize(n_stars_);

		for (Size i = 0; i < n_wormholes_; ++i)
		{
			Size from, to;
			Weight t;
			read(from, to, t);
			wormholes_[from].push_back({to, t});
		}
	}

	virtual void solve(unsigned int) override
	{
		if (!has_negative_cycle(wormholes_, 0))
			write("not ");
		write_ln("possible");
	}

private:
	Size n_stars_;
	Adjacency_list wormholes_;
};

MAIN


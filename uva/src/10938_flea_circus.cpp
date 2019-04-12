/*********************************************************************
Flea circus
-----------
UVa ID: 109 38

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

// Note: a better solution based on Lowest Common Ancestor
// exists, see problem UVa 12238 Ants Colony

#include "base.hpp"
#include "util.hpp"
#include <cassert>
#include <vector>
#include <utility>

using Size = unsigned int;
using Vertex_list = std::vector<Size>;
using Adjacency_list = std::vector<Vertex_list>;

template<class Func>
bool depth_first_search(
	const Adjacency_list& graph, std::vector<Size>& path, Size vertex, Func func)
{
	for (auto succ : graph[vertex])
	{
		if (path.size() > 1 && succ == *(path.end() - 2))
			continue;

		path.push_back(succ);
		if (func(succ) || !depth_first_search(graph, path, succ, func))
			return false;

		path.pop_back();
	}

	return true;
}

// Returns the vertices in the middle of the path that connects the vertices
// (first) and (last), for the odd-length path (result.first) = (result.second)
std::pair<Size, Size> mid_vertices(const Adjacency_list& graph, Size first, Size last)
{
	assert(first < graph.size() && last < graph.size());

	std::vector<Size> path{first};
	depth_first_search(graph, path, first, [last](Size vertex) { return vertex == last; });

	const auto n = path.size();
	return {path[(n - 1) / 2], path[n / 2]};
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		if (!read(n_sites_) || n_sites_ == 0)
			return false;

		assert(1 <= n_sites_ && n_sites_ <= 5'000);

		tree_.clear();
		tree_.resize(n_sites_);
		for (Size i = 1; i < n_sites_; ++i)
		{
			Size s1, s2;
			read(s1, s2);
			--s1;
			--s2;
			tree_[s1].push_back(s2);
			tree_[s2].push_back(s1);
		}

		Size n_start_positions;

		read(n_start_positions);
		assert(1 <= n_start_positions && n_start_positions <= 500);
		read_vec(n_start_positions, start_positions_);

		// To zero-based indexing
		for (auto& p : start_positions_)
			--p.first, --p.second;

		return true;
	}

	virtual void solve(unsigned int) override
	{
		for (auto& p : start_positions_)
		{
			auto mv = mid_vertices(tree_, p.first, p.second);
			sort2(++mv.first, ++mv.second);

			if (mv.first == mv.second)
				write_ln("The fleas meet at ", mv.first, '.');
			else
				write_ln("The fleas jump forever between ", mv.first, " and ", mv.second, '.');
		}
	}

private:
	Size n_sites_;
	Adjacency_list tree_;
	std::vector<std::pair<Size, Size>> start_positions_;
};



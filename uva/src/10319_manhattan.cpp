/*********************************************************************
Manhattan
---------
UVa ID: 103 19

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

using Size = unsigned int;
using Capacity = unsigned int;

struct Crossing
{
	Size street;
	Size avenue;
};

class Two_sat
{
public:
	struct Var
	{
		Size index;
		bool flag;

		Var operator~() const
		{
			return {index, !flag};
		}
	};

public:
	Two_sat(Size n_vars)
	{
		implication_graph_.resize(2 * n_vars);
	}

	// Adds clause (a)
	void add_clause(Var a)
	{
		implication_graph_[index(~a)].push_back(index(a));
	}

	// Adds clause (a v b)
	void add_clause(Var a, Var b)
	{
		implication_graph_[index(~a)].push_back(index(b));
		implication_graph_[index(~b)].push_back(index(a));
	}

	bool is_satisfiable() const
	{
		// 2SAT is satifiable if for all variables there are
		// no paths from (a) to (~a) and from (~a) to (a)
		return !has_a_and_not_a_in_same_scc();
	}

private:
	struct Dfs
	{
		static constexpr auto invalid_index = static_cast<Size>(-1);

		Size index = invalid_index;
		Size low_link = invalid_index;
		bool is_on_stack = false;
	};

private:
	static Size index(Var a)
	{
		return 2 * a.index + a.flag;
	}

	// Check if the vertices (v) and (w) correspond
	// to variables (a) and (~a)
	static bool a_and_not_a(Size v, Size w)
	{
		return (v ^ w) == 1;
	}

	bool has_a_and_not_a_in_same_scc() const
	{
		Size dfs_index = 0;
		std::vector<Dfs> dfs(implication_graph_.size());
		std::vector<Size> sccs;

		for (Size v = 0; v < implication_graph_.size(); ++v)
			if (dfs[v].index == Dfs::invalid_index)
				if (has_a_and_not_a_in_same_scc(v, dfs_index, dfs, sccs))
					return true;

		return false;
	}

	bool has_a_and_not_a_in_same_scc(
		Size at, Size& dfs_index, std::vector<Dfs>& dfs, std::vector<Size>& sccs) const
	{
		sccs.push_back(at);
		dfs[at].is_on_stack = true;
		dfs[at].index = dfs[at].low_link = dfs_index++;

		for (auto to : implication_graph_[at])
		{
			if (dfs[to].index == Dfs::invalid_index)
				has_a_and_not_a_in_same_scc(to, dfs_index, dfs, sccs);
			if (dfs[to].is_on_stack)
				dfs[at].low_link = std::min(dfs[at].low_link, dfs[to].low_link);
		}

		if (dfs[at].low_link == dfs[at].index)
		{
			const auto r_root = std::find(sccs.rbegin(), sccs.rend(), at);
			assert(r_root != sccs.rend());

			const auto root = (r_root + 1).base();
			std::sort(root, sccs.end());

			if (std::adjacent_find(root, sccs.end(), a_and_not_a) != sccs.end())
				return true;

			std::for_each(root, sccs.end(), [&dfs](Size w) { dfs[w].is_on_stack = false; });
			sccs.erase(root, sccs.end());
		}

		return false;
	}

private:
	std::vector<std::vector<Size>> implication_graph_;
};

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		Size n_routes;
		read(n_streets_, n_avenues_, n_routes);

		routes_.clear();
		for (Size i = 0; i < n_routes; ++i)
		{
			Crossing from, to;
			read(from.street, from.avenue, to.street, to.avenue);
			--from.street, --from.avenue; // To zero-based indexing
			--to.street, --to.avenue;
			assert(from.street < n_streets_ && to.street < n_streets_);
			assert(from.avenue < n_avenues_ && to.avenue < n_avenues_);

			routes_.push_back({from, to});
		}
	}

	virtual void solve(unsigned int) override
	{
		Two_sat two_sat(n_streets_ + n_avenues_);
		for (auto& route : routes_)
		{
			const auto& from = route.first;
			const auto& to = route.second;

			if (from.street == to.street)
			{
				assert(from.avenue != to.avenue);

				Two_sat::Var v = {from.street, to.avenue > from.avenue};
				two_sat.add_clause(v);
			}
			else if (from.avenue == to.avenue)
			{
				assert(from.street != to.street);

				Two_sat::Var v = {from.avenue + n_streets_, to.street > from.street};
				two_sat.add_clause(v);
			}
			else
			{
				assert(from.street != to.street && from.avenue != to.avenue);

				// First route: vs1 ^ va1
				Two_sat::Var vs1 = {from.street, to.avenue > from.avenue};
				Two_sat::Var va1 = {to.avenue + n_streets_, to.street > from.street};

				// Second route: vs2 ^ va2
				Two_sat::Var vs2 = {from.avenue + n_streets_, to.street > from.street};
				Two_sat::Var va2 = {to.street, to.avenue > from.avenue};

				// (vs1 ^ va1) v (vs2 ^ va2) = (vs1 v vs2) ^ (vs1 v va2) ^ (va1 v vs2) ^ (va1 v va2)
				two_sat.add_clause(vs1, vs2);
				two_sat.add_clause(vs1, va2);
				two_sat.add_clause(va1, vs2);
				two_sat.add_clause(va1, va2);
			}
		}

		write_ln(two_sat.is_satisfiable() ? "Yes" : "No");
	}

private:
	Size n_streets_, n_avenues_;
	std::vector<std::pair<Crossing, Crossing>> routes_;
};



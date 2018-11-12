/*********************************************************************
Ordering
--------
UVa ID: 008 72

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <sstream>
#include <string>
#include <vector>

using Size = unsigned int;
using Vertex_list = std::vector<Size>;
using Adjacency_list = std::vector<Vertex_list>;

class Topologicals_sorts
{
public:
	Topologicals_sorts(const Adjacency_list& graph) : graph_(graph)
	{ }

	std::vector<std::vector<Size>> enumerate_topological_sorts() const
	{
		std::vector<Vertex_list> lists;

		std::vector<Size> in_degrees(graph_.size(), 0);
		for (auto& vertex : graph_)
			for (auto succ : vertex)
				++in_degrees[succ];

		Vertex_list list;
		next_sort(in_degrees, lists, list);

		return lists;
	}

private:
	void next_sort(std::vector<Size>& in_degrees, std::vector<Vertex_list>& lists, Vertex_list& list) const
	{
		for (Size vertex = 0; vertex < graph_.size(); ++vertex)
			if (in_degrees[vertex] == 0)
			{
				list.push_back(vertex);
				--in_degrees[vertex];
				for (auto succ : graph_[vertex])
					--in_degrees[succ];

				next_sort(in_degrees, lists, list);

				// Backtrack
				list.pop_back();
				++in_degrees[vertex];
				for (auto succ : graph_[vertex])
					++in_degrees[succ];
			}

		if (list.size() == graph_.size())
			lists.push_back(list);
	}

private:
	const Adjacency_list& graph_;
};

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		ignore_line();

		std::string variables_str, constraints_str;
		read_ln(variables_str);
		read_ln(constraints_str);

		std::istringstream variables(variables_str);
		std::istringstream constraints(constraints_str);

		char var;

		variables_.clear();
		constraints_.clear();

		while (variables >> var)
			variables_.push_back(var);

		std::sort(variables_.begin(), variables_.end());

		constraints_.resize(variables_.size());
		while (constraints >> var)
		{
			char less, var2;
			constraints >> less >> var2;
			assert(less == '<');
			constraints_[var_index(var)].push_back(var_index(var2));
		}
	}

	Size var_index(char v) const
	{
		const auto pos = std::find(variables_.begin(), variables_.end(), v);
		assert(pos != variables_.end());

		return static_cast<Size>(pos - variables_.begin());
	}

	virtual void solve(unsigned int i_case) override
	{
		if (i_case > 0)
			write_ln();

		const Topologicals_sorts ts(constraints_);
		const auto sorts = ts.enumerate_topological_sorts();

		for (auto& sort : sorts)
		{
			write_vec(sort, [this](Size i) { return variables_[i]; }, ' ');
			write_ln();
		}

		if (sorts.empty())
			write_ln("NO");
	}

private:
	std::vector<char> variables_;
	Adjacency_list constraints_;
};

MAIN(CP)

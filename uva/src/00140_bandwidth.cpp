/*********************************************************************
Bandwidth
---------
UVa ID: 001 40

Given a graph (V;E) where V is a set of nodes and E is a set of arcs
in V x V, and an ordering on the elements in V, then the bandwidth
of a node v is defined as the maximum distance in the ordering between
v and any node to which it is connected in the graph. The bandwidth
of the ordering is then defined as the maximum of the individual
bandwidths. Write a program that will find the ordering of a graph
that minimises the bandwidth.

Input
-----
Input will consist of a series of graphs. Each graph will appear on a
line by itself. The entire file will be terminated by a line consisting
of a single "#". For each graph, the input will consist of a series
of records separated by ";". Each record will consist of a node name
(a single upper case character in the range "A" to "Z"), followed
by a ":" and at least one of its neighbours. The graph will contain
no more than 8 nodes.

Output
------
Output will consist of one line for each graph, listing the ordering
of the nodes followed by an arrow " -> " and the bandwidth for that
ordering. All items must be separated from their neighbours by exactly
one space. If more than one ordering produces the same bandwidth, then
choose the smallest in lexicographic ordering, that is the one that
would appear first in an alphabetic listing.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

using Graph = std::vector<std::vector<std::size_t>>;

class Min_bandwidth
{
public:
	Min_bandwidth(const Graph& graph) : graph_(graph), size_(graph_.size())
	{
		seen_positions_.assign(size_, false);
		curr_permutation_.resize(size_);
		min_bandwidth_ = static_cast<std::size_t>(-1);
		backtrack();
	}

	std::size_t bandwidth() const
	{
		return min_bandwidth_;
	}

	std::vector<std::size_t> permutation() const
	{
		std::vector<std::size_t> inv_permutation(size_);
		for (std::size_t i = 0; i < size_; ++i)
			inv_permutation[min_permutation_[i]] = i;
		return inv_permutation;
	}

private:
	std::size_t get_bandwidth()
	{
		std::size_t bandwidth = 0;
		for (std::size_t i = 0; i < size_; ++i)
		{
			const auto pi = curr_permutation_[i];
			for (const auto j : graph_[i])
			{
				const auto pj = curr_permutation_[j];
				const auto dist = pi > pj ? pi - pj : pj - pi;
				bandwidth = std::max(bandwidth, dist);
			}
		}

		return bandwidth;
	}

	void backtrack(std::size_t pos = 0)
	{
		if (pos == size_)
			if (const auto bandwidth = get_bandwidth(); bandwidth < min_bandwidth_)
			{
				min_bandwidth_ = bandwidth;
				min_permutation_ = curr_permutation_;
			}

		for (std::size_t j = 0; j < size_; ++j)
		{
			if (seen_positions_[j])
				continue;

			seen_positions_[j] = true;
			curr_permutation_[j] = pos;
			backtrack(pos + 1);
			seen_positions_[j] = false;
		}
	}

	const Graph& graph_;
	const std::size_t size_;

	std::vector<char> seen_positions_;
	std::vector<std::size_t> curr_permutation_;
	std::vector<std::size_t> min_permutation_;
	std::size_t min_bandwidth_;
};

class Vertex_map
{
public:
	std::size_t init_and_get_size(const std::string& descr)
	{
		std::vector<char> letters;
		const auto is_letter = [](char ch) { return 'A' <= ch && ch <= 'Z'; };
		std::copy_if(descr.begin(), descr.end(), std::back_inserter(letters), is_letter);
		std::sort(letters.begin(), letters.end());
		const auto last = std::unique(letters.begin(), letters.end());
		letters.erase(last, letters.end());

		std::fill(map_.begin(), map_.end(), invalid_index);
		std::size_t i = 0;
		for (auto vertex : letters)
			map_[char_to_index(vertex)] = i++;

		return letters.size();
	}

	std::size_t operator[](char vertex) const
	{
		return map_[char_to_index(vertex)];
	}

	char find(std::size_t index) const
	{
		const auto it = std::find(map_.begin(), map_.end(), index);
		assert(it != map_.end());
		return index_to_char(it - map_.begin());
	}

private:
	static std::size_t char_to_index(char ch)
	{
		return static_cast<std::size_t>(ch - 'A');
	}

	static char index_to_char(std::ptrdiff_t index)
	{
		return static_cast<char>(index + 'A');
	}

private:
	static constexpr std::size_t invalid_index = -1;
	static constexpr std::size_t map_max_size = 'Z' - 'A' + 1;

	std::array<std::size_t, map_max_size> map_;
};

template<typename T>
void push_if_not_there(std::vector<T>& vec, T value)
{
	if (const auto it = std::find(vec.begin(), vec.end(), value); it == vec.end())
		vec.push_back(std::move(value));
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::string descr;
		if (!read_ln(descr) || descr == "#")
			return false;

		const auto size = map_.init_and_get_size(descr);
		graph_.clear();
		graph_.resize(size);

		for (std::size_t i = 0; i < descr.length(); ++i)
		{
			const auto v = map_[descr[i++]];
			assert(descr[i] == ':');

			while (++i < descr.length() && descr[i] != ';')
				push_if_not_there(graph_[v], map_[descr[i]]);
		}

		return true;
	}

	virtual void solve(unsigned int) override
	{
		Min_bandwidth min_bandwidth{graph_};
		const auto perm = min_bandwidth.permutation();
		write_range(perm.begin(), perm.end(), [this](auto i) { return map_.find(i); }, ' ');
		write_ln(" -> ", min_bandwidth.bandwidth());
	}

private:
	Vertex_map map_;
	Graph graph_;
};

MAIN

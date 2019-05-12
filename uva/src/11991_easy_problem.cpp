/*********************************************************************
Easy problem from Rujia Liu?
----------------------------
UVa ID: 119 91

Given an array, your task is to find the k-th occurrence (from left
to right) of an integer v. To make the problem more difficult
(and interesting!), you'll have to answer m such queries.

Input
-----
There are several test cases. The first line of each test case
contains two integers n, m (1 <= n, m <= 100'000), the number of
elements in the array, and the number of queries. The next line
contains n positive integers not larger than 1'000'000. Each of the
following m lines contains two integer k and v (1 <= k <= n,
1 <= v <= 1'000'000). The input is terminated by end-of-file (EOF).

Output
------
For each query, print the 1-based location of the occurrence.
If there is no such element, output "0" instead.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <vector>

template<class It>
std::size_t dist(It first, It last)
{
	return static_cast<std::size_t>(last - first);
}

using T = unsigned int;

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::size_t n, n_queries;
		if (!read(n, n_queries))
			return false;

		numbers_.clear();
		numbers_.reserve(n);
		for (std::size_t i = 0; i < n; ++i)
		{
			T v;
			read(v);
			numbers_.emplace_back(v, i);
		}

		queries_.resize(n_queries);
		for (auto& q : queries_)
		{
			read(q);
			--q.first; // to zero-based indexing
		}

		return true;
	}

	virtual void solve(unsigned int) override
	{
		std::sort(numbers_.begin(), numbers_.end());

		for (const auto& q : queries_)
		{
			const auto value = q.second;
			const auto index = q.first;

			const auto pos = std::lower_bound(
				numbers_.begin(), numbers_.end(), value, [](std::pair<T, std::size_t>& a, T b) { return a.first < b; });

			const auto found = pos != numbers_.end() && pos->first == value && index < dist(pos, numbers_.end()) &&
							   (pos + index)->first == value;

			if (found)
				write_ln(1 + (pos + index)->second); // to one-based indexing
			else
				write_ln(0);
		}
	}

private:
	std::vector<std::pair<T, std::size_t>> numbers_;
	std::vector<std::pair<std::size_t, T>> queries_;
};

MAIN


/*********************************************************************
Subset sum
----------
UVa ID: 129 11

Given a set of integers, your task is to determine how many different
non-empty subsets sum up to a target value.

Input
-----
The input consists of several test cases. The first line of each test
case is a line containing two integers N and T, the number of items
of the original set of integers and the target value. After that comes
one line with the N integers s_i that belong to the original sets.
	1 <= N <= 40, -10^9 <= T, s_i <= 10^9

Output
------
For each test case print on a single line an integer indicating the
number of different non-empty subsets that sum up to the target value.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <vector>

template<class It, typename T = typename std::iterator_traits<It>::value_type>
std::size_t count_subsets_matching_sum(It first, const std::size_t size, const T sum)
{
	const auto size1 = size / 2;
	const auto size2 = size - size1;

	std::vector<T> sums(1ul << size1, 0);
	for (std::size_t i = 0; i < size1; ++i, ++first)
		sums[1ul << i] = *first;

	for (std::size_t i = 1; i < (1ul << size1); ++i)
	{
		const auto i_wo_lsb = i & (i - 1);
		const auto i_lsb    = i - i_wo_lsb;
		sums[i] = sums[i_wo_lsb] + sums[i_lsb];
	}

	std::sort(sums.begin(), sums.end());

	std::size_t cnt = 0;
	for (std::size_t i = 0; i < (1ul << size2); ++i)
	{
		T curr_sum = sum;

		auto it = first;
		for (std::size_t mask = 1; mask != (1ul << size2); mask <<= 1, ++it)
			if (i & mask)
				curr_sum -= *it;

		const auto range = std::equal_range(sums.begin(), sums.end(), curr_sum);
		cnt += std::distance(range.first, range.second);
	}

	return cnt - (sum == 0);
}

using T = long long;

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::size_t size;
		if (!read(size, sum_))
			return false;

		set_.clear();
		read_vec(size, set_);
		return true;
	}

	virtual void solve(unsigned int) override
	{
		write_ln(count_subsets_matching_sum(set_.begin(), set_.size(), sum_));
	}

private:
	std::vector<T> set_;
	T sum_;
};

MAIN

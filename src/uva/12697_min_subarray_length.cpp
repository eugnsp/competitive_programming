/*********************************************************************
Minimal subarray length
-----------------------
UVa ID: 126 97

You are given an integer sequence of length N and another value X.
You have to find a contiguous subsequence of the given sequence such
that the sum is greater or equal to X. And you have to find that
segment with minimal length.

Input
-----
First line of the input file contains T the number of test cases. Each
test case starts with a line containing two integers N
(1 <= N <= 500'000) and X (-10^9 <= X <= 10^9). Next line contains N
integers denoting the elements of the sequence. These integers will be
between -10^9 and 10^9 inclusive.

Output
------
For each test case output the minimum length of the sub array whose
sum is greater or equal to X. If there is no such array, output '-1'.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <optional>
#include <vector>

using T = int;

template<class It>
std::optional<std::size_t> min_subarray_length_with_sum(It first, It last, T min_sum)
{
	std::size_t min_len = static_cast<std::size_t>(-1);
	for (T sum = 0; first != last; ++first)
	{
		if (sum > 0)
			sum += *first;
		else
			sum = *first;

		if (sum >= min_sum)
		{
			auto left = first;
			for (auto s = *left; s < min_sum; s += *left)
				--left;

			const auto len = static_cast<std::size_t>(first - left + 1);
			min_len = std::min(min_len, len);
			if (min_len == 1)
				break;
		}
	}

	if (min_len != static_cast<std::size_t>(-1))
		return min_len;
	else
		return {};
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t n;
		read(n, min_sum_);

		set_.clear();
		read_vec(n, set_);
	}

	virtual void solve(unsigned int) override
	{
		const auto r = min_subarray_length_with_sum(set_.begin(), set_.end(), min_sum_);
		if (r)
			write_ln(*r);
		else
			write_ln("-1");
	}

private:
	std::vector<T> set_;
	T min_sum_;
};

MAIN

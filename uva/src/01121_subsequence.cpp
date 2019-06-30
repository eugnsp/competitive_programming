/*********************************************************************
Subsequence
-----------
UVa ID: 011 21

A sequence of N positive integers (10 < N < 100'000), each of them
less than or equal 10'000, and a positive integer S ( S < 100'000'000)
are given. Write a program to find the minimal length of the
subsequence of consecutive elements of the sequence, the sum of which
is greater than or equal to S.

Input
-----
Many test cases will be given. For each test case the program has
to read the numbers N and S, separated by an interval, from the
first line. The numbers of the sequence are given in the second line
of the test case, separated by intervals. The input will finish with
the end of file.

Output
------
For each the case the program has to print the result on separate line
of the output file.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cstddef>
#include <optional>
#include <vector>

template<class It, typename S>
std::optional<std::size_t> min_length_geq_sum(It first, It last, const S& sum)
{
	std::optional<std::size_t> min_length;
	S curr_sum{};

	auto right = first;
	while (right != last)
	{
		curr_sum += *right++;
		while (curr_sum >= sum)
		{
			curr_sum -= *first++;
			const auto len = static_cast<std::size_t>(right - first);
			min_length = min_length ? std::min(*min_length, len) : len;
		}
	}

	return min_length;
}

using T = unsigned int;

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::size_t size;
		if (!read(size, sum_))
			return false;

		vec_.clear();
		return read_vec(size, vec_);
	}

	virtual void solve(unsigned int) override
	{
		auto min_length = min_length_geq_sum(vec_.begin(), vec_.end(), sum_);
		write_ln(min_length ? *min_length : 0);
	}

private:
	std::vector<T> vec_;
	T sum_;
};

MAIN

/*********************************************************************
Subarray with given sum
-----------------------

Given an unsorted array A of size N of non-negative integers, find
a continuous sub-array which adds to a given number.

Input
-----
The first line of input contains an integer T denoting the number of
test cases. Then T test cases follow. Each test case consists of two
lines. The first line of each test case is N and S, where N is the
size of array and S is the sum. The second line of each test case
contains N space separated integers denoting the array elements.

Output
------
For each testcase, in a new line, print the starting and ending
positions (1-based indexing) of first such occuring subarray from
the left if sum equals to subarray, else print "-1".

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <utility>
#include <vector>

template<class It, typename T>
std::pair<It, It> find_contiguous_sum(It first, It last, const T& sum)
{
	assert(sum >= 0);
	if (sum == 0)
		return {first, first};

	T curr_sum = 0;
	for (auto right = first; right != last;)
	{
		curr_sum += *right++;
		while (curr_sum > sum)
			curr_sum -= *first++;
		if (curr_sum == sum)
			return {first, right};
	}

	return {last, last};
}

using T = unsigned long long;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t size;
		read(size, sum_);

		seq_.clear();
		read_vec(size, seq_);
	}

	virtual void solve(unsigned int) override
	{
		auto range = find_contiguous_sum(seq_.begin(), seq_.end(), sum_);
		if (range.first == seq_.end())
			write_ln(-1);
		else
			write_ln(range.first - seq_.begin() + 1, ' ', range.second - seq_.begin());
	}

private:
	T sum_;
	std::vector<T> seq_;
};

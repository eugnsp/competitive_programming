/*********************************************************************
Maximum index
-------------
URL: https://practice.geeksforgeeks.org/problems/maximum-index/0

Given an array A of positive integers. The task is to find the
maximum of j - i subjected to the constraint of A[i] <= A[j].

Input
-----
The first line of input contains an integer T denoting the number of
test cases. Then T test cases follow. The first line of each test case
contains an integer N denoting the size of the array A in the next
line are N space separated values of the array A.

Output
------
Print the maximum difference of the indexes i and j in a separtate
line.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <memory>
#include <vector>

template<typename T>
std::size_t max_dist_sorted_pair(const std::vector<T>& seq)
{
	const auto n = seq.size();
	const auto less = [&seq](std::size_t i, std::size_t j)
		{ return seq[i] < seq[j]; };

	// `max_right(i)` is the position of the rightmost
	// largest element in the suffix `seq[i..]`
	std::vector<std::size_t> max_right(n);

	max_right.back() = n - 1;
	for (auto i = n - 1; i > 0; --i)
		max_right[i - 1] = std::max(max_right[i], i - 1, less);

	std::size_t max_dist = 0;
	for (std::size_t i = 0, j = 0; i < n; ++i)
		// Move the right boundary as far as possible
		while (!less(max_right[j], i))
		{
			j = max_right[j];
			max_dist = std::max(max_dist, j - i);
			if (++j == n)
				return max_dist;
		}

	return max_dist;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(seq_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(max_dist_sorted_pair(seq_));
	}

private:
	std::vector<int> seq_;
};

MAIN(CP)

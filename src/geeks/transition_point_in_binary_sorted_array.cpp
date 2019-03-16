/*********************************************************************
Find transition point
---------------------
URL: https://practice.geeksforgeeks.org/problems/find-transition-point/1

You are given a sorted array containing only numbers 0 and 1. Find the
transition point efficiently. Transition point is a point where "0"
ends and "1" begins.

Input
-----
The first line of input contains an integer T denoting the number of
test cases. Then T test cases follow. The first line of each test case
contains an integer N denoting the size of the array in the next
line are N space separated values of the array.

Output
------
Print the position of a transition point.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <vector>

template<class It>
It transition_point(It first, It last)
{
	// Loop invariants:
	// 	[first0, first): 	contains zeros
	// 	[first, last)`: 	is not yet processed
	// 	[last, last0): 		contains ones

	while (first != last)
	{
		const auto mid = first + (last - first) / 2;
		if (*mid == 0)
			first = mid + 1;
		else
			last = mid;
	}

	return first;
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
		auto pos = transition_point(seq_.begin(), seq_.end());
		write_ln(pos - seq_.begin());
	}

private:
	std::vector<unsigned int> seq_;
};

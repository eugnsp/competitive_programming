/*********************************************************************
Count smaller elements on the right side
----------------------------------------
URL: https://practice.geeksforgeeks.org/problems/count-smaller-elements/0

Given an array A of N integers. For each element of the array count
the number of smaller elements on the right side of this element.

Input
-----
The first line of input contains an integer T denoting the number of
test cases. Then T test cases follow. The first line of each test case
contains an integer N denoting the size of the array A in the next
line are N space separated values of the array A.

Output
------
For each test case output the numbers of smaller elements.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <vector>

template<class It, typename T>
void three_way_partition(It first, It last, const T& a, const T& b)
{
	assert(a <= b);

	// Loop invariants:
	// 	[first, i): 	*it < a
	// 	[i, j):			a <= *it <= b
	// 	[j, k):			unpartitioned
	// 	[k, last):		b < *it

	// At the beginning: i = j = first, k = last
	// At the end: j = k

	auto i = first;
	auto j = first;
	auto k = last;
	while (j != k)
		if (*j < a)
			std::iter_swap(i++, j++);
		else if (b < *j)
			std::iter_swap(j, --k);
		else
			++j;
}

using T = int;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(seq_);
		read(a_, b_);
	}

	virtual void solve(unsigned int) override
	{
		three_way_partition(seq_.begin(), seq_.end(), a_, b_);
		write_vec(seq_, ' ');
		write_ln();
	}

private:
	std::vector<T> seq_;
	T a_;
	T b_;
};

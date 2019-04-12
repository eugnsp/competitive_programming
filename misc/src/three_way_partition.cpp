/*********************************************************************
Three way partition
-------------------

Partition the given array such that all elements smaller than (a)
come first, all elements in range [a, b] come next, all elements
greater than (b) appear in the end.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <vector>

template<class It, typename T>
void three_way_partition(const It first, It const last, const T& a, const T& b)
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

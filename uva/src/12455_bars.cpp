/*********************************************************************
Bars
----
UVa ID: 124 55

Some things grow if you put them together. We have some metallic bars,
theirs length known, and, if necessary, we want to solder some of them
in order to obtain another one being exactly a given length long. No
bar can be cut up. Is it possible?

Input
-----
The first line of the input contains an integer, t, 0 <= t <= 50,
indicating the number of test cases. For each test case, three lines
appear, the first one contains a numbern, 0 <= n <= 1000, representing
the length of the bar we want to obtain. The second line contains a
number p, 1 <= p <= 20, representing the number of bars we have. The
third line of each test case contains p numbers, representing the
lengths of the p bars.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

// Note: search space is small, and this naive solution
// using backtracking is fast enough

#include "base.hpp"
#include <cassert>
#include <vector>

template<class It, typename T>
bool is_sum_decomposable(It first, It last, T total_value)
{
	if (total_value == 0)
		return true;
	if (first == last)
		return false;
	if (total_value == *first)
		return true;
	if (total_value > *first && is_sum_decomposable(first + 1, last, total_value - *first))
		return true;
	return is_sum_decomposable(first + 1, last, total_value);
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(length_);
		assert(length_ <= 1000);

		read_size_vec(lengths_);
	}

	virtual void solve(unsigned int) override
	{
		const auto f = is_sum_decomposable(lengths_.begin(), lengths_.end(), length_);
		write_ln(f ? "YES" : "NO");
	}

private:
	unsigned int length_;
	std::vector<unsigned int> lengths_;
};

MAIN


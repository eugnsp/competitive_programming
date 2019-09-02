/*********************************************************************
Equilibrium point
-----------------

Find the first equilibrium point in the given array. Equilibrium point
is a position such that the sum of elements before it is equal to the
sum of elements after it.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>

template<typename It, typename T = typename std::iterator_traits<It>::value_type>
It equilibrium_point(It first, const It last)
{
	for (T left_sum = T{0}, right_sum = std::accumulate(first, last, T{0}); first < last; ++first)
	{
		right_sum -= *first;
		if (left_sum == right_sum)
			return first;
		left_sum += *first;
	}

	return last;
}

using T = int;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(seq_);
	}

	virtual void solve(unsigned int) override
	{
		auto pt = equilibrium_point(seq_.begin(), seq_.end());
		if (pt != seq_.end())
			write_ln(pt - seq_.begin() + 1);
		else
			write_ln(-1);
	}

private:
	std::vector<T> seq_;
};

MAIN

/*********************************************************************
Bitonic array search
--------------------

Find the given element in the given bitonic array of distinct elements.
An array is called bitonic if it consists of an non-decreasing
sequence of elements followed by a non-increasing one.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <functional>
#include <vector>

// Returns the iterator to the maximum value in the bitonic range [first, last)
// of distinct elements
template<class It>
It find_bitonic_max(It first, It last)
{
	assert(first != last);
	--last;

	// Invariants:
	// ..., first]   is increasing
	// [last, ...    is decreasing

	while (first != last)
	{
		const auto mid = first + (last - first) / 2;
		if (*mid < *(mid + 1))
			first = mid + 1;
		else
			last = mid;
	}

	return first;
}

template<class It, typename T>
It find_bitonic(const It first, const It last, const T& value)
{
	if (first == last)
		return last;

	const auto max = find_bitonic_max(first, last);
	assert(max != last);

	if (*max < value)
		return last;
	if (*max == value)
		return max;

	const auto pos_l = std::lower_bound(first, max, value, std::less<T>{});
	if (pos_l != max && *pos_l == value)
		return pos_l;

	const auto pos_r = std::lower_bound(max + 1, last, value, std::greater<T>{});
	if (pos_r != last && *pos_r == value)
		return pos_r;

	return last;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(seq_);
		read(n_);
	}

	virtual void solve(unsigned int) override
	{
		const auto pos = find_bitonic(seq_.begin(), seq_.end(), n_);
		if (pos != seq_.end())
			write_ln(pos - seq_.begin());
		else
			write_ln(-1);
	}

private:
	std::vector<int> seq_;
	int n_;
};

/*********************************************************************
Minimum element in sorted rotated array
---------------------------------------

In the given sorted and rotated array of distinct elements find the
smallest element.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <iterator>
#include <vector>

template<class It>
It min_element_sorted_rotated(const It first, const It last)
{
	auto it1 = first;
	auto it2 = last;

	// Invariants:
	// all elements in the range [first, it1) are greater
	// than all elements in the range [it2, last)

	// At the end: it1 = it2,
	// (it2) points to the smallest element if (it2 != last)
	// (first) points to the smallest element otherwise

	while (it1 != it2)
	{
		const auto mid = it1 + (it2 - it1) / 2;
		if (*first <= *mid)
			it1 = mid + 1;
		else
			it2 = mid;
	}

	if (it2 == last)
		it2 = first;
	return it2;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(vec_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(*min_element_sorted_rotated(vec_.begin(), vec_.end()));
	}

private:
	std::vector<unsigned int> vec_;
};

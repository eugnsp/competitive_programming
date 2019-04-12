/*********************************************************************
Majority element
----------------

Find the majority element in the given array. A majority element is
the element that appears more than N/2 times in the array, where N
is the array size.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <vector>

template<class It>
It majority_element(const It first, const It last)
{
	typename std::iterator_traits<It>::difference_type counter = 0;

	auto candidate = first;
	for (auto it = first; first != last; ++it)
	{
		if (counter == 0)
			candidate = it;
		if (*it == *candidate)
			++counter;
		else
			--counter;
	}

	counter = std::count(first, last, *candidate);
	const auto size = std::distance(first, last);
	if (counter > size / 2)
		return candidate;
	else
		return last;
}

using Element = unsigned int;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(seq_);
	}

	virtual void solve(unsigned int) override
	{
		const auto m = majority_element(seq_.begin(), seq_.end());

		if (m != seq_.end())
			write_ln(*m);
		else
			write_ln(-1);
	}

private:
	std::vector<Element> seq_;
};



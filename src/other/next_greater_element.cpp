/*********************************************************************
Next greater element
--------------------

For the given array of distinct elements for each elemen find the
next greater element in order of their appearance in the array.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <stack>
#include <vector>

template<class It>
std::vector<It> prev_greater_elements(It first, const It last)
{
	assert(first <= last);

	const auto n = static_cast<std::size_t>(last - first);
	std::vector<It> iterators;
	iterators.reserve(n);

	std::stack<It> greaters;
	for (; first != last; ++first)
	{
		while (!greaters.empty() && *greaters.top() < *first)
			greaters.pop();
		iterators.push_back(!greaters.empty() ? greaters.top() : last);
		greaters.push(first);
	}

	return iterators;
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
		const auto greaters = prev_greater_elements(vec_.rbegin(), vec_.rend());
		for (auto it = greaters.rbegin(); it != greaters.rend(); ++it)
			if (*it == vec_.rend())
				write(-1, ' ');
			else
				write(**it, ' ');
		write_ln();
	}

private:
	std::vector<unsigned long long> vec_;
};



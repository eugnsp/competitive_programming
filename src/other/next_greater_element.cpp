/*********************************************************************
Next greater element
--------------------

For the given array of distinct elements for each elemen find the
next greater element in order of their appearance in the array.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <stack>
#include <vector>

template<class It>
std::vector<It> next_greater_elements(const It first, const It last)
{
	const auto n = static_cast<std::size_t>(last - first);
	std::vector<It> next(n);

	std::stack<It> greaters;
	auto it = last;
	for (std::size_t i = n; i > 0; --i)
	{
		--it;
		while (!greaters.empty() && *greaters.top() < *it)
			greaters.pop();
		next[i - 1] = !greaters.empty() ? greaters.top() : last;
		greaters.push(it);
	}

	return next;
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
		const auto greaters = next_greater_elements(vec_.begin(), vec_.end());
		for (auto it : greaters)
			if (it == vec_.end())
				write(-1, ' ');
			else
				write(*it, ' ');
		write_ln();
	}

private:
	std::vector<unsigned long long> vec_;
};



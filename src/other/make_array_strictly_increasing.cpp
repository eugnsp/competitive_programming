/*********************************************************************
Make array strictly increasing
------------------------------

For the given array of positive integers find the minimum number of
replacements of its elements to make the array strictly increasing.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <vector>

template<class It>
std::size_t count_min_ops(const It first, const It last)
{
	// At each iteration fin[i] is an iterator to the smallest value in the
	// range [first, last)' such that there exists a longest non-decreasing
	// sequence of length (i + 1) with the last element (*fin[i]); the range
	// [first, last)' is obtained from the range [first, last) by shifting
	// down all its elements by their indices: *it' = *it - (it - first)
	std::vector<It> fin;

	for (auto it = first; it != last; ++it)
	{
		const auto pos = std::upper_bound(fin.begin(), fin.end(), it,
			[](It l, It r)
			{
				if (*l < *r)
					return static_cast<std::ptrdiff_t>(*r - *l) > r - l;
				else
					return static_cast<std::ptrdiff_t>(*l - *r) < l - r;
			});

		if (pos != fin.end())
			*pos = it;
		else
			fin.push_back(it);
	}

	return static_cast<std::size_t>(last - first) - fin.size();
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
		write_ln(count_min_ops(seq_.begin(), seq_.end()));
	}

private:
	std::vector<unsigned int> seq_;
};

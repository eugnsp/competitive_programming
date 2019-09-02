/*********************************************************************
Stable index
------------

Find the position of the first element such that A[i] = i for the
given non-decreasing array, A[0] <= A[1] <= ... <= A[n-1].

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <type_traits>
#include <vector>

template<class It>
It find_first_stable_pos(It first, const It last)
{
	static_assert(std::is_integral_v<typename std::iterator_traits<It>::value_type>);
	assert(std::is_sorted(first, last));

	typename std::iterator_traits<It>::difference_type index = 0;
	while (first != last)
	{
		const auto curr = static_cast<std::ptrdiff_t>(*first);
		if (curr == index)
			return first;
		else if (curr > index)
		{
			const auto skip = curr - index;
			if (last - first <= skip)
				return last;
			first += skip;
			index += skip;
		}
		else
		{
			++index;
			++first;
		}
	}

	return last;
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
		const auto pos = find_first_stable_pos(seq_.begin(), seq_.end());
		if (pos != seq_.end())
			write_ln(pos - seq_.begin());
		else
			write_ln("Not found");
	}

private:
	std::vector<int> seq_;
};

MAIN

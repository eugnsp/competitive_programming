/*********************************************************************
Array with unit adjacent difference search
------------------------------------------

Find the given value in the given array in which the difference
between all adjacent elements equals 1.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iterator>
#include <type_traits>
#include <vector>

template<class It, typename T>
It adjacent_one_find(It first, const It last, const T& value)
{
	static_assert(std::is_integral_v<typename std::iterator_traits<It>::value_type>);
	using Diff = typename std::iterator_traits<It>::difference_type;

	if (first == last)
		return last;

	while (*first != value)
	{
		const auto dist = std::abs(static_cast<Diff>(*first) - static_cast<Diff>(value));
		if (dist >= last - first)
			return last;
		first += dist;
	}

	return first;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(seq_);
		read(value_);
	}

	virtual void solve(unsigned int) override
	{
		auto pos = adjacent_one_find(seq_.begin(), seq_.end(), value_);
		assert(pos == std::find(seq_.begin(), seq_.end(), value_));

		if (pos != seq_.end())
			write_ln(pos - seq_.begin());
		else
			write_ln("Not found");
	}

private:
	std::vector<int> seq_;
	int value_;
};

MAIN

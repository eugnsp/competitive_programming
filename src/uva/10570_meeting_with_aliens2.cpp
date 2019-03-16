/*********************************************************************
Meeting with aliens
-------------------
UVa ID: 105 70

The aliens are in an important meeting just before landing on the
earth. All the aliens sit around around table during the meeting.
Aliens are numbered sequentially from 1 to N. It's a precondition of
the meeting that i-th alien will sit between (i - 1)-th and (i + 1)-th
alien. 1st alien will sit between 2nd and N-th alien. Though the
ordering of aliens are fixed but their positions are not fixed. Right
before the start of the meeting the alienssometimes face a common
problem of not maintaining the proper order. This occurs as no alien
has a fixed position. Two maintain the proper order, two aliens can
exchange their positions. The aliens want to know the minimum number
of exchange operations necessary to fix the order.

Input
-----
Input will start with a positive integer N (3 <= N <= 500) the number
of aliens. In next few lines there will be N distinct integers from
1 to N indicating the current ordering of aliens. Input is terminated
by a case where N = 0. This case should not be processed. There will
be not more than 100 datasets.

Output
------
For each set of input print the minimum exchange operations required
to fix the ordering of aliens.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <vector>

template<class It>
std::size_t min_n_swaps(const It first, const It last, const bool reversed)
{
	const auto n = static_cast<std::size_t>(last - first);

	std::vector<typename std::iterator_traits<It>::value_type> range;
	range.resize(2 * n);
	if (!reversed)
	{
		std::copy(first, last, range.begin());
		std::copy(first, last, range.begin() + n);
	}
	else
	{
		std::copy(first, last, range.rbegin());
		std::copy(first, last, range.rbegin() + n);
	}

	std::vector<bool> seen(n, false);

	auto min_n_swaps = n;
	for (std::size_t i = 0; i < n; ++i)
	{
		const auto start = range.begin() + i;
		std::size_t n_cycles = 0;

		std::fill(seen.begin(), seen.end(), false);
		for (std::size_t j = 0; j < n; ++j)
			if (!seen[j])
			{
				auto it = start + j;
				while (!seen[*it])
				{
					seen[*it] = true;
					it = start + *it;
				}

				++n_cycles;
			}

		if (n_cycles == n)
			return 0;
		min_n_swaps = std::min(min_n_swaps, n - n_cycles);
	}

	return min_n_swaps;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_size_vec(positions_,
			[](std::size_t i) { return i - 1; });	// to zero-based indexing
	}

	virtual void solve(unsigned int) override
	{
		const auto n_swaps = min_n_swaps(positions_.begin(), positions_.end(), false);
		if (n_swaps == 0)
			write_ln(0);
		else
		{
			const auto n_swaps_rev = min_n_swaps(positions_.begin(), positions_.end(), true);
			write_ln(std::min(n_swaps, n_swaps_rev));
		}
	}

private:
	std::vector<std::size_t> positions_;
};



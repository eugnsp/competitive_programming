/*********************************************************************
The jackpot
-----------
UVa ID: 106 84

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <limits>
#include <vector>

// Returns the sum of contiguous subarray within the array ([first, last))
// which has the largest sum
template<class It, typename T = typename std::iterator_traits<It>::value_type>
T kadane_max_sum(It first, It last)
{
	if (first == last)
		return 0;

	auto sum = std::numeric_limits<T>::min();
	auto max_sum = sum;

	for (; first != last; ++first)
	{
		if (sum >= 0)
			sum += *first;
		else
			sum = *first;

		max_sum = std::max(max_sum, sum);
	}

	return max_sum;
}

class CP : public CP2
{
private:
	using Bet = int;

private:
	virtual bool read_input() override
	{
		return read_size_vec(bets_);
	}

	virtual void solve(unsigned int) override
	{
		const auto max_gain = kadane_max_sum(bets_.cbegin(), bets_.cend());
		if (max_gain > 0)
			write_ln("The maximum winning streak is ", max_gain, ',');
		else
			write_ln("Losing streak.");
	}

private:
	std::vector<Bet> bets_;
};

MAIN


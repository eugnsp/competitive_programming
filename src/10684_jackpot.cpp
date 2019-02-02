/*********************************************************************
The jackpot
-----------
UVa ID: 106 84

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_kadane_max_sum.hpp"
#include <cstddef>
#include <iterator>
#include <algorithm>
#include <vector>

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

MAIN(CP)

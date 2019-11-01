/*********************************************************************
Let me count the ways
---------------------
UVa ID: 003 57

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_coin_change.hpp"
#include <array>

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(amount_);
	}

	virtual void solve(unsigned int) override
	{
		const std::array<unsigned int, 5> coins = {1, 5, 10, 25, 50};

		const auto n = n_ways_change<unsigned int>(coins, amount_);
		if (n > 1)
			write_ln("There are ", n, " ways to produce ", amount_, " cents change.");
		else
			write_ln("There is only 1 way to produce ", amount_, " cents change.");
	}

private:
	unsigned int amount_;
};

MAIN

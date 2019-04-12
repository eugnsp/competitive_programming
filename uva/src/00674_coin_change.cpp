/*********************************************************************
Coin change
-----------
UVa ID: 006 74

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
		write_ln(n_ways_change<unsigned int>(coins, amount_));
	}

private:
	unsigned int amount_;
};



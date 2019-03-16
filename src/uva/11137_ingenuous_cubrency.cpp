/*********************************************************************
Ingenuous cubrency
------------------
UVa ID: 111 37

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_coin_change.hpp"
#include <array>
#include <algorithm>

class CP : public CP2
{
private:
	virtual void init() override
	{
		unsigned int i = 0;
		std::generate(coins_.begin(), coins_.end(), [&i]() {
			++i;
			return i * i * i;
		});
	}

private:
	virtual bool read_input() override
	{
		return read(amount_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(n_ways_change<unsigned long long>(coins_, amount_));
	}

private:
	std::array<unsigned int, 21> coins_;
	unsigned int amount_;
};



/*********************************************************************
Ingenuous cubrency
------------------
UVa ID: 11137

Goal:	the number of ways to pay the given amount using
		the coins available in Cubeland.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_coin_change.hpp"
#include <array>
#include <algorithm>
#include <iostream>

class Ingenuous_cubrency : public CP2
{
private:
	virtual void init() override
	{
		unsigned int i = 0;
		std::generate(coins_.begin(), coins_.end(), [&i]()
		{
			++i;
			return i * i * i;
		});
	}

private:
	virtual bool read_input() override
	{
		// <amount>

		std::cin >> amount_;
		return !!std::cin;
	}

	virtual void solve(std::size_t) override
	{
		std::cout << n_ways_change<unsigned long long>(coins_, amount_) << '\n';
	}

private:
	std::array<unsigned int, 21> coins_;
	unsigned int amount_;
};

int main()
{
	Ingenuous_cubrency p;
	return p.run();
}

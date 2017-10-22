/*********************************************************************
Let me count the ways
---------------------
UVa ID: 357

Goal:	determine the number of different combinations of US coins
		(1c, 5c, 10c, 25c, 50c) which may be used to produce
		a given amount of money.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_coin_change.hpp"
#include <array>
#include <iostream>

class Count_the_ways : public CP2
{
private:
	virtual bool read_input() override
	{
		// <amount>
		
		std::cin >> amount_;
		return !!std::cin;
	}

	virtual void solve(std::size_t) override
	{
		const std::array<unsigned int, 5> coins = {1, 5, 10, 25, 50};

		const auto n = n_ways_change<unsigned int>(coins, amount_);
		if (n > 1)
			std::cout << "There are " << n << " ways to produce " << amount_ << " cents change.\n";
		else
			std::cout << "There is only 1 way to produce " << amount_ << " cents change.\n";
	}

private:
	unsigned int amount_;
};

int main()
{
	Count_the_ways p;
	return p.run();
}

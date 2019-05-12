/*********************************************************************
Dollars
-------
UVa ID: 001 47

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_coin_change.hpp"
#include <array>
#include <cmath>
#include <iomanip>

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(amount_) && amount_ != 0;
	}

	virtual void solve(unsigned int) override
	{
		using T = unsigned int;
		const std::array<T, 11> coins = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};

		const auto amount_in_cents = static_cast<T>(std::round(100 * amount_));
		const auto n = n_ways_change<unsigned long long>(coins, amount_in_cents);

		write(std::fixed, std::setprecision(2));
		write_ln(std::setw(6), amount_, std::setw(17), n);
	}

private:
	double amount_;
};

MAIN


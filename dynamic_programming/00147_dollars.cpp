/*********************************************************************
Dollars
-------
UVa ID: 147

Goal:	determine, for any given amount of money, in how many ways
		that amount may be made up using coins and notes.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_coin_change.hpp"
#include <array>
#include <cmath>
#include <iomanip>

class Dollars : public CP2
{
private:
	virtual bool read_input(std::istream& in) override
	{
		// <amount>

		in >> amount_;
		return amount_ != 0;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		using T = unsigned int;		
		const std::array<T, 11> coins =
			{5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};

		const auto amount_in_cents = static_cast<T>(std::round(100 * amount_));
		const auto n = n_ways_change<unsigned long long>(coins, amount_in_cents);
		
		out << std::fixed << std::setprecision(2);
		out << std::setw(6) << amount_ << std::setw(17) << n << '\n';
	}

private:
	double amount_;
};

int main()
{
	Dollars p;
	return p.run();
}
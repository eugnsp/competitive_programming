/*********************************************************************
Dollars
-------
UVa ID: 001 47

New Zealand currency consists of $100, $50, $20, $10, and $5 notes
and $2, $1, 50c, 20c, 10c and 5c coins. Write a program that will
determine, for any given amount, in how many ways that amount maybe
made up. Changing the order of listing does not increase the count.
Thus 20c may be made up in 4 ways: 1 x 20c, 2 x 10c, 10c + 2 x 5c,
and 4 x 5c.

Input
-----
Input will consist of a series of real numbers no greater than $300.00
each on a separate line. Each amount will be valid, that is will be
a multiple of 5c. The file will be terminated by a line containing
zero (0.00).

Output
------
Output will consist of a line for each of the amounts in the input,
each line consisting of the amount of money (with two decimal places
and right justified in a field of width 6), followed by the number
of ways in which that amount may be made up, right justified in
a field of width 17.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <array>
#include <cmath>
#include <iomanip>
#include <type_traits>
#include <vector>

// Returns for given (amount) of money, in how many ways that amount
// may be made up of coins with denominations (coins)
// (each coin can be used unlimited number of times)
template<typename Size, class Coins>
Size n_ways_change(const Coins& coins, typename Coins::value_type amount)
{
	using Coin = typename Coins::value_type;

	static_assert(std::is_unsigned_v<Coin>);
	static_assert(std::is_unsigned_v<Size>);
	assert(amount > 0);

	std::vector<Size> n_ways(amount + 1, 0);
	n_ways[0] = 1;

	for (const auto coin : coins)
		for (Coin i = 1; i <= amount; ++i)
			if (i >= coin)
				n_ways[i] += n_ways[i - coin];

	return n_ways.back();
}

using T = unsigned int;

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(amount_) && amount_ != 0;
	}

	virtual void solve(unsigned int) override
	{
		const auto amount_in_cents = static_cast<T>(std::round(100 * amount_));
		const std::array<T, 11> coins = {5, 10, 20, 50, 100, 200, 500, 1'000, 2'000, 5'000, 10'000};
		const auto n = n_ways_change<unsigned long long>(coins, amount_in_cents);

		write_ln(std::fixed, std::setprecision(2), std::setw(6), amount_, std::setw(17), n);
	}

private:
	double amount_;
};

MAIN

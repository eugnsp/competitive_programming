// Dollars
// -------
//
// Goal: determine, for any given amount of money, in how many ways that amount
// may be made up using coins and notes.
//
// UVa ID: 147
// This file is covered by the LICENSE file in the root of this project.

#include "dp_coin_change.hpp"
#include <array>
#include <cmath>
#include <iostream>
#include <iomanip>

using T = unsigned int;

// <amount>

int main()
{
	const std::array<T, 11> coins = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};

	std::cout.precision(2);
	std::cout.setf(std::ios_base::fixed);

	for(;;)
	{
		double amount;
		std::cin >> amount;

		const auto amount_in_cents = static_cast<T>(std::round(100 * amount));
		if (amount_in_cents == 0)
			break;

		const auto n = n_ways_change<unsigned long long>(coins, amount_in_cents);
		std::cout << std::setw(6) << amount << std::setw(17) << n << '\n';
	}

	return 0;
}
// Dollars
// -------
//
// Goal: determine, for any given amount of money, in how many ways that amount
// may be made up using coins and notes.
//
// UVa ID: 147
// This file is covered by the LICENSE file in the root of this project.

#include "coin_change.hpp"
#include <cstddef>
#include <array>
#include <cmath>
#include <cstdio>
#include <iostream>

using T = unsigned int;

// <amount>

int main()
{
	const std::array<T, 11> coins = {5, 10, 20, 50, 100, 200, 500, 1000, 2000, 5000, 10000};

	for(;;)
	{
		double amount;
		std::cin >> amount;

		const T amount_in_cents = static_cast<T>(std::round(100 * amount));
		if (amount_in_cents == 0)
			break;

		const auto n = n_ways_change(coins, amount_in_cents);

		char n_str[6 + 17 + 1];
		std::sprintf(n_str, "%6.2f%17zu", amount, n);
		std::cout << n_str << '\n';
	}

	return 0;
}
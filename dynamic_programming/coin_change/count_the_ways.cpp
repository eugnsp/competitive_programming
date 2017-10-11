// Let me count the ways
// ---------------------
//
// Goal: determine the number of different combinations of US coins
// (1c, 5c, 10c, 25c, 50c) which may be used to produce a given amount of money.
//
// UVa ID: 357 
// This file is covered by the LICENSE file in the root of this project.

#include "coin_change.hpp"
#include <cstddef>
#include <array>
#include <iostream>

using T = unsigned int;

// <amount>

int main()
{
	const std::array<T, 5> coins = {1, 5, 10, 25, 50};

	for(;;)
	{
		T amount;
		std::cin >> amount;

		if (!std::cin)
			break;

		const auto n = n_ways_change(coins, amount);
		if (n > 1)
			std::cout << "There are " << n << " ways to produce " << amount << " cents change.\n";
		else
			std::cout << "There is only 1 way to produce " << amount << " cents change.\n";
	}

	return 0;
}

// Coin change
// -----------
//
// Goal: determine in how many ways given amount of money
// may be made up using a fixed set of coins and notes.
//
// UVa ID: 674
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

		std::cout << n_ways_change(coins, amount) << '\n';
	}

	return 0;
}

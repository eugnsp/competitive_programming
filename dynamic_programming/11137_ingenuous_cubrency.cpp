// Ingenuous cubrency
// ------------------
//
// Goal: the number of ways to pay the given amount using the coins available in Cubeland.
//
// UVa ID: 11137
// This file is covered by the LICENSE file in the root of this project.

#include "dp_coin_change.hpp"
#include <array>
#include <algorithm>
#include <iostream>

using T = unsigned int;

// <amount>

int main()
{
	std::array<T, 21> coins;
	T i = 0;
	std::generate(coins.begin(), coins.end(), [&i]() { ++i; return i * i * i; });

	for (;;)
	{
		T amount;
		if (!(std::cin >> amount))
			break;

		std::cout << n_ways_change<unsigned long long>(coins, amount) << '\n';
	}

	return 0;
}

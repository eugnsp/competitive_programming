// Dividing coins
// --------------
//
// Goal: determine the most fair division of a collection
// of coins between two persons.
//
// UVa ID: 562
// This file is covered by the LICENSE file in the root of this project.

#include "zero_one_knapsack.hpp"
#include <cstddef>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <iostream>
#include <cassert>

using T = unsigned int;

// Returns the minimum positive difference between the amount the two
// persons obtain when they divide the (coins) in the most fair way
T divide_coins_min_diff(const std::vector<T>& coins)
{
	assert(std::all_of(coins.begin(), coins.end(), [](T c) { return c > 0; }));

	const auto n = coins.size();
	if (n == 0)
		return 0;

	const auto total_sum = std::accumulate(coins.begin(), coins.end(), static_cast<T>(0));
	const auto half_total = total_sum / 2;

	const auto coin = [&coins](std::size_t i) { return coins[i]; };
	const auto half_fairest = knapsack_max_value(n, half_total, coin, coin);
	assert(half_fairest <= half_total);

	return total_sum - 2 * half_fairest;
}

// <number of test cases>
// <number of coins>
// <coin_1> <coin_n>

int main()
{
	std::size_t n_tests;
	std::cin >> n_tests;

	while (n_tests--)
	{
		std::size_t n;
		std::cin >> n;

		std::vector<T> coins(n);
		if (n > 0)
			std::copy_n(std::istream_iterator<T>(std::cin), coins.size(), coins.begin());

		std::cout << divide_coins_min_diff(coins) << '\n';
	}

	return 0;
}
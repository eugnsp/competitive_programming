// Exact change
// ------------
//
// Goal: find the best combination of coins to pay at least as much as the given value.
//
// UVa ID: 11517
// This file is covered by the LICENSE file in the root of this project.

#include "coin_change.hpp"
#include <cstddef>
#include <utility>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>

using T = unsigned int;

// Returns the total amount paid and the number of coins used
// in the best combination to pay at least as much as the given value (price)
// using coins with denominations (coins)
std::pair<T, std::size_t> best_change(const std::vector<T>& coins, T price, T max_amount_to_pay)
{
	auto change = zero_one_coin_change(coins, max_amount_to_pay);
	while (change[price].n == static_cast<decltype(change[0].n)>(-1))
	{
		++price;
		if (price > max_amount_to_pay)
			return {0, 0};
	}

	return {price, change[price].n};
}

// <number of test cases>
// <price>
// <number of coins>
// <denomination_1>
// ... 
// <denomination_n>

int main()
{
	std::size_t n_tests;
	std::cin >> n_tests;

	while (n_tests--)
	{
		T price;
		std::size_t n;

		std::cin >> price >> n;

		std::vector<T> coins(n);
		std::copy_n(std::istream_iterator<T>(std::cin), coins.size(), coins.begin());

		const auto change = best_change(coins, price, static_cast<T>(20000));
		std::cout << change.first << ' ' << change.second << '\n';
	}

	return 0;
}

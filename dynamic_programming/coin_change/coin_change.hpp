#pragma once
#include <cstddef>
#include <vector>
#include <type_traits>

// Returns for given (amount) of money, in how many ways that amount
// may be made up of coins with denominations (coins)
template<class Coins>
std::size_t n_ways_change(const Coins& coins, typename Coins::value_type amount)
{
	static_assert(std::is_unsigned<typename Coins::value_type>::value, "Type should be unsigned");

	std::vector<std::size_t> n_ways(amount + 1, 0);
	n_ways[0] = 1;

	for (auto coin : coins)
		for (std::size_t i = 1; i <= amount; ++i)
			if (i >= coin)
				n_ways[i] += n_ways[i - coin];

	return n_ways.back();
}

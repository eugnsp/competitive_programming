// Coin change common routines
// ---------------------------
//
// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <cstddef>
#include <vector>
#include <algorithm>
#include <type_traits>
#include <cassert>

struct Coin_change
{
	std::size_t n;
	std::size_t coin_index;
};

// For every integer amount of money in the range [0, (amount)] returns
// the array of the minimum number of coins with denominations (coins)
// and the indices of the last selected coin that add up to that amount
// (each coin can be used unlimited number of times)
template<class Coins>
std::vector<Coin_change> coin_change(const Coins& coins, typename Coins::value_type amount)
{
	using Coin = typename Coins::value_type;

	static_assert(std::is_unsigned_v<Coin>, "Coin denomination type should be unsigned");
	assert(std::all_of(coins.begin(), coins.end(), [](Coin c) { return c > 0; }));
	assert(amount > 0);

	constexpr auto max_size = static_cast<std::size_t>(-1);
	std::vector<Coin_change> m(amount + 1, {max_size, 0});

	m[0].n = 0;
	for (std::size_t j = 0; j < coins.size(); ++j)
	{
		const auto coin = coins[j];
		for (auto i = coin; i <= amount; ++i)
		{
			auto r = m[i - coin].n;
			if (r != max_size && ++r < m[i].n)
			{
				m[i].n = r;
				m[i].coin_index = j;
			}
		}
	}

	return m;
}

// For every integer amount of money in the range [0, (amount)] returns
// the array of the minimum number of coins with denominations (coins)
// and the indices of the last selected coin that add up to that amount
// (each coin can be used only once)
template<class Coins>
std::vector<Coin_change> zero_one_coin_change(const Coins& coins, typename Coins::value_type amount)
{
	using Coin = typename Coins::value_type;

	static_assert(std::is_unsigned_v<Coin>, "Coin denomination type should be unsigned");
	assert(std::all_of(coins.begin(), coins.end(), [](Coin c) { return c > 0; }));
	assert(amount > 0);

	constexpr auto max_size = static_cast<std::size_t>(-1);
	std::vector<Coin_change> m(amount + 1, {max_size, 0});

	m[0].n = 0;
	for (std::size_t j = 0; j < coins.size(); ++j)
	{
		const auto coin = coins[j];
		for (auto i = amount; i >= coin; --i)
		{
			auto r = m[i - coin].n;
			if (r != max_size && ++r < m[i].n)
			{
				m[i].n = r;
				m[i].coin_index = j;
			}
		}
	}

	return m;
}

// Returns for given (amount) of money, in how many ways that amount
// may be made up of coins with denominations (coins)
// (each coin can be used unlimited number of times)
template<typename Size, class Coins>
Size n_ways_change(const Coins& coins, typename Coins::value_type amount)
{
	using Coin = typename Coins::value_type;

	static_assert(std::is_unsigned_v<Coin>, "Coin denomination type should be unsigned");
	static_assert(std::is_unsigned_v<Size>, "Size type should be unsigned");
	assert(std::all_of(coins.begin(), coins.end(), [](Coin c) { return c > 0; }));
	assert(amount > 0);

	std::vector<Size> n_ways(amount + 1, 0);
	n_ways[0] = 1;

	for (auto coin : coins)
		for (Coin i = 1; i <= amount; ++i)
			if (i >= coin)
				n_ways[i] += n_ways[i - coin];

	return n_ways.back();
}

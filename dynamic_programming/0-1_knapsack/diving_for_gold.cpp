// Diving for gold
// ---------------
//
// Goal: select which treasures to pick to maximize the quantity of gold recovered
//
// UVa ID: 990
// This file is covered by the LICENSE file in the root of this project.

#include "zero_one_knapsack.hpp"
#include <cstddef>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using T = unsigned int;

// Returns the maximum amount of gold and the indices of the recovered treasures
std::pair<T, std::vector<T>> diving_for_gold(
	T max_time, T speed, const std::vector<T>& depths, const std::vector<T>& amounts)
{
	assert(std::all_of(depths.begin(), depths.end(), [](T d) { return d > 0; }));
	assert(std::all_of(amounts.begin(), amounts.end(), [](T a) { return a > 0; }));

	const auto n = static_cast<T>(depths.size());

	const auto weight = [&depths, speed](std::size_t i) { return 3 * speed * depths[i]; };
	const auto value = [&amounts](std::size_t i) { return amounts[i]; };
	return knapsack_max_value_and_items(n, max_time, weight, value);
}

// <maximum time> <speed>
// <number of treasures>
// <depth_1> <amount_1>
// ...
// <depth_n> <amount_n>

int main()
{
	for (bool first = true; ; first = false)
	{
		T max_time;
		std::cin >> max_time;

		if (!std::cin)
			break;

		T speed;
		std::cin >> speed;

		T n;
		std::cin >> n;

		std::vector<T> depths(n);
		std::vector<T> amounts(n);
		for (std::size_t i = 0; i < n; ++i)
			std::cin >> depths[i] >> amounts[i];

		const auto treasures = diving_for_gold(max_time, speed, depths, amounts);

		if (!first)
			std::cout << '\n';

		std::cout << treasures.first << '\n' << treasures.second.size() << '\n';
		for (std::size_t i = 0; i < treasures.second.size(); ++i)
			std::cout << depths[treasures.second[i]] << ' ' << amounts[treasures.second[i]] << '\n';
	}

	return 0;
}
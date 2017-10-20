// Diving for gold
// ---------------
//
// Goal: select which treasures to pick to maximize the quantity of gold recovered
//
// UVa ID: 990
// This file is covered by the LICENSE file in the root of this project.

#include "dp_zero_one_knapsack.hpp"
#include <cstddef>
#include <utility>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using T = unsigned int;

struct Treasure
{
	T amount;
	T depth;
};

// Returns the maximum amount of gold and the indices of the recovered treasures
std::pair<T, std::vector<std::size_t>> diving_for_gold(
	T max_time, T speed, const std::vector<Treasure>& treasures)
{
	assert(std::all_of(treasures.begin(), treasures.end(),
		[](const Treasure& t) { return t.amount > 0 && t.depth > 0; }));

	const auto weight = [&treasures, speed](std::size_t i) { return 3 * speed * treasures[i].depth; };
	const auto value = [&treasures](std::size_t i) { return treasures[i].amount; };
	return knapsack_max_value_and_items(treasures.size(), max_time, weight, value);
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
		if (!(std::cin >> max_time))
			break;

		T speed;
		T n;

		std::cin >> speed >> n;

		std::vector<Treasure> treasures(n);
		for (auto& t : treasures)
			std::cin >> t.depth >> t.amount;

		const auto ts = diving_for_gold(max_time, speed, treasures);

		if (!first)
			std::cout << '\n';

		std::cout << ts.first << '\n' << ts.second.size() << '\n';
		for (const auto i : ts.second)
			std::cout << treasures[i].depth << ' ' << treasures[i].amount << '\n';
	}

	return 0;
}
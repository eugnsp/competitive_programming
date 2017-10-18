// Luggage
// -------
//
// Goal: determine if it is possible to distribute the suitcases
// into the boots so that the two boots weigh the same.
//
// UVa ID: 10664
// This file is covered by the LICENSE file in the root of this project.

#include "zero_one_knapsack.hpp"
#include <cstddef>
#include <utility>
#include <vector>
#include <algorithm>
#include <limits>
#include <numeric>
#include <string>
#include <sstream>
#include <iostream>
#include <cassert>

using T = unsigned int;

// Returns true if it is possible to distribute the suitcases with (weights)
// into the boots so that the two boots weigh the same, returns false otherwise
bool is_distribution_possible(const std::vector<T>& weights)
{
	assert(std::all_of(weights.begin(), weights.end(), [](T c) { return c > 0; }));

	const auto total_weight = std::accumulate(weights.begin(), weights.end(), static_cast<T>(0));
	if (total_weight % 2 == 1)
		return false;

	const auto weight = [&weights](std::size_t i) { return weights[i]; };
	const auto max_weight_in_one_boot = knapsack_max_value(weights.size(), total_weight / 2, weight, weight);
	return (max_weight_in_one_boot == total_weight / 2);
}

// <number of test cases>
// <weight_1> ... <weight_n>

int main()
{
	std::size_t n_tests;
	std::cin >> n_tests;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	while (n_tests--)
	{
		std::stringstream ss;
		std::string weights_str;

		std::getline(std::cin, weights_str);
		ss << weights_str;

		std::vector<T> weights;
		for (T weight; ss >> weight; )
			weights.push_back(weight);

		const bool is_possible = is_distribution_possible(weights);
		std::cout << (is_possible ? "YES\n" : "NO\n");
	}

	return 0;
}
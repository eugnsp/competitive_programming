// Best coalitions
// ---------------
//
// Goal: given a distribution of shares of stock, determine the maximum
// percentage of the last year's profit that the given stockholder may win.
//
// UVa ID: 11658
// This file is covered by the LICENSE file in the root of this project.

#include "zero_one_knapsack.hpp"
#include <cstddef>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <cassert>

using T = unsigned int;

// Return the maximum percentage of the profit that the (target_stockholder) may win
// in a joint stock company of (n_stockholders) with (shares) 
double best_coalition(T n_stockholders, T target_stockholder, std::vector<T> shares)
{
	assert(!shares.empty());
	assert(target_stockholder < n_stockholders);

	const auto n = static_cast<T>(shares.size() - 1);

	const auto total_shares = std::accumulate(shares.begin(), shares.end(), static_cast<T>(0));
	const auto target_share = shares[target_stockholder];
	shares.erase(shares.begin() + target_stockholder);

	const auto weight = [&shares](std::size_t i) { return shares[i]; };
	const auto value = [&shares](std::size_t i) { return shares[i]; };
	const auto excluded_shares = knapsack_max_value(n, (total_shares - 1) / 2, weight, value);

	return static_cast<double>(target_share) / (total_shares - excluded_shares);
}

// Input format:
// <number of stockholders> <stockholder>
// <share_1>
// ...
// <share_n>

int main()
{	
	for (;;)
	{
		T n_stockholders, target_stockholder;
		std::cin >> n_stockholders >> target_stockholder;

		if (n_stockholders == 0 && target_stockholder == 0)
			break;

		std::vector<T> shares(n_stockholders);
		std::generate_n(shares.begin(), shares.size(), []()
		{
			float share;
			std::cin >> share;
			return static_cast<T>(std::round(100 * share));
		});

		assert(std::accumulate(shares.begin(), shares.end(), 0) == 10000);
		
		--target_stockholder;	// To zero-based indexing
		const auto best_share = best_coalition(n_stockholders, target_stockholder, shares);

		char best_share_str[10];
		std::sprintf(best_share_str, "%.2f", std::round(best_share * 10000) / 100);
		std::cout << best_share_str << '\n';
	}

	return 0;
}
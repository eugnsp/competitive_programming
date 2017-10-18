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
#include <iostream>
#include <iomanip>
#include <cassert>

using T = unsigned int;

// Return the maximum percentage of the profit that the (target_stockholder) may win
// in a joint stock company of (n_stockholders) with (shares) 
double best_coalition(std::size_t n_stockholders, std::size_t target_stockholder, std::vector<T> shares)
{
	assert(!shares.empty());
	assert(target_stockholder < n_stockholders);

	const auto n = shares.size() - 1;
	if (n == 0)
		return 1;

	const auto total_shares = std::accumulate(shares.begin(), shares.end(), static_cast<T>(0));
	const auto target_share = shares[target_stockholder];
	shares.erase(shares.begin() + target_stockholder);

	// To get the maximum profit we should exclude stockholders with highest shares,
	// but not too many of them (their total share should be less than 50%)
	const auto share = [&shares](std::size_t i) { return shares[i]; };
	const auto excluded_shares = knapsack_max_value(n, (total_shares - 1) / 2, share, share);

	return static_cast<double>(target_share) / (total_shares - excluded_shares);
}

// Input format:
// <number of stockholders> <stockholder>
// <share_1>
// ...
// <share_n>

int main()
{	
	std::cout.precision(2);
	std::cout.setf(std::ios_base::fixed);

	for (;;)
	{
		std::size_t n_stockholders, target_stockholder;
		std::cin >> n_stockholders >> target_stockholder;

		if (n_stockholders == 0 && target_stockholder == 0)
			break;

		std::vector<T> shares(n_stockholders);
		std::generate_n(shares.begin(), shares.size(), []()
		{
			double share;
			std::cin >> share;
			return static_cast<T>(std::round(100 * share));
		});

		assert(std::accumulate(shares.begin(), shares.end(), 0) == 10000);
		
		--target_stockholder;	// To zero-based indexing
		const auto best_share = best_coalition(n_stockholders, target_stockholder, shares);
		std::cout << std::round(best_share * 10000) / 100 << '\n';
	}

	return 0;
}
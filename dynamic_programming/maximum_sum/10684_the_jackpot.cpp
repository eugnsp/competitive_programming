// The jackpot
// -----------
//
// Goal: identify the maximum possible gain out of a sequence of bets.
//
// UVa ID: 10684
// This file is covered by the LICENSE file in the root of this project.

#include "kadane_max_sum.hpp"
#include <cstddef>
#include <iterator>
#include <algorithm>
#include <vector>
#include <iostream>

using T = int;

// <number of bets>
// <bet_1>
// ... 
// <bet_n>

int main()
{
	for (;;)
	{
		T n;
		std::cin >> n;

		if (n == 0)
			break;

		std::vector<T> bets(n);
		std::copy_n(std::istream_iterator<T>(std::cin), bets.size(), bets.begin());

		const auto max_gain = kadane_max_sum(bets.cbegin(), bets.cend());
		if (max_gain > 0)
			std::cout << "The maximum winning streak is " << max_gain << ".\n";
		else
			std::cout << "Losing streak.\n";
	}

	return 0;
}
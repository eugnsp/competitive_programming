// Jill rides again
// ----------------
//
// Goal: given the "niceness" of the route segments, identify
// the best part to cycle for each bus route (for the best part
// the sum of "niceness" values of the segments is maximized).
//
// UVa ID: 507
// This file is covered by the LICENSE file in the root of this project.

#include "kadane_max_sum.hpp"
#include <cstddef>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>

using T = int;

// <number of routes>
// <number of bus stops>
// <niceness_1>
// ... 
// <niceness_n>

int main()
{
	std::size_t n_tests;
	std::cin >> n_tests;

	for (std::size_t r = 1; r <= n_tests; ++r)
	{
		std::size_t n_stops;
		std::cin >> n_stops;

		std::vector<T> nicenesses(n_stops - 1);
		std::copy_n(std::istream_iterator<T>(std::cin), nicenesses.size(), nicenesses.begin());
		
		const auto max_sum = kadane_max_sum_and_range(nicenesses.cbegin(), nicenesses.cend());

		if (max_sum.first > 0)
			std::cout << "The nicest part of route " << r << " is between stops "
				<< (max_sum.second.first - nicenesses.begin()) + 1 << " and "
				<< (max_sum.second.second - nicenesses.begin()) + 1 << "\n";
		else
			std::cout << "Route " << r << " has no nice parts\n";
	}

	return 0;
}
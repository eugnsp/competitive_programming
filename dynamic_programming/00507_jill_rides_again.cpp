/*********************************************************************
Jill rides again
----------------
UVa ID: 507

Goal:	given the "niceness" of the route segments, identify the best
		part to cycle (for the best part the sum of "niceness" values
		of the segments is maximized).

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_kadane_max_sum.hpp"
#include <cstddef>
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <cassert>

class Jill : public CP1
{
private:
	virtual void read_input() override
	{
		// <number of bus stops>
		// <niceness_1>
		// ... 
		// <niceness_n>

		std::size_t n_stops;
		std::cin >> n_stops;
		assert(n_stops >= 2);

		nicenesses_.resize(n_stops - 1);
		std::copy_n(std::istream_iterator<int>(std::cin), nicenesses_.size(), nicenesses_.begin());
	}

	virtual void solve(std::size_t i_case) override
	{
		const auto max_sum = kadane_max_sum_and_range(nicenesses_.cbegin(), nicenesses_.cend());

		if (max_sum.first > 0)
			std::cout << "The nicest part of route " << i_case + 1 << " is between stops "
					  << std::distance(nicenesses_.cbegin(), max_sum.second.first) + 1 << " and "
					  << std::distance(nicenesses_.cbegin(), max_sum.second.second) + 1 << "\n";
		else
			std::cout << "Route " << i_case + 1 << " has no nice parts\n";
	}

private:
	std::vector<int> nicenesses_;
};

int main()
{
	Jill p;
	return p.run();
}

/*********************************************************************
Exact sum
---------
UVa ID: 110 57

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>
#include <utility>

using Price = unsigned int;
using Prices = std::vector<Price>;

// Returns an iterator (it) such that (2 * *(it-1) <= value) and (2 * *it >= value),
// precondition: such an iterator should be a valid one
Prices::const_iterator mid(const Prices& vector, Price value)
{
	const auto half_value = (value + 1) / 2;
	const auto m = std::lower_bound(vector.begin(), vector.end(), half_value);
	return (value % 2 == 1) || (*m != half_value) ? m : m + 1;
}

// Returns two elements such that their sum equals (sum), if multiple pairs
// exist, returns the one with minimal distance between elements
// (precondition: such two elements should exist).
std::pair<Price, Price> find_elements_with_sum(Prices vector, Price sum)
{
	assert(vector.size() >= 2);
	std::sort(vector.begin(), vector.end());

	auto it1 = mid(vector, sum);
	auto it2 = vector.rbegin() + (vector.end() - it1);

	while (it1 != vector.end() && it2 != vector.rend())
	{
		const auto s = *it1 + *it2;
		if (s == sum)
			return {*it2, *it1};

		if (s < sum)
			++it1;
		else
			++it2;
	}

	// Unreachable by the precondition
	return {0, 0};
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_size_vec(prices_) && read(sum_);
	}

	virtual void solve(unsigned int) override
	{
		const auto prices = find_elements_with_sum(prices_, sum_);
		write_ln(
			"Peter should buy books whose prices are ", prices.first, " and ", prices.second, '.');
		write_ln();
	}

private:
	Prices prices_;
	Price sum_;
};

MAIN(CP)

// Dividing coins
// --------------
//
// Goal: determine the most fair division of a collection
// of coins between two persons.
//
// UVa ID: 562
// This file is covered by the LICENSE file in the root of this project.

#include "base.hpp"
#include "dp_zero_one_knapsack.hpp"
#include <cstddef>
#include <vector>
#include <algorithm>
#include <numeric>
#include <iterator>
#include <iostream>
#include <cassert>

class Dividing_coins : public Program1
{
private:
	using T = unsigned int;

private:
	virtual void read_input() override
	{
		// <number of coins>
		// <coin_1> <coin_n>

		std::size_t n;
		std::cin >> n;

		coins_.resize(n);
		if (n > 0)
			std::copy_n(std::istream_iterator<T>(std::cin), coins_.size(), coins_.begin());
	}

	virtual void solve(std::size_t) override
	{
		const auto n = coins_.size();
		if (n == 0)
		{
			std::cout << "0\n";
			return;
		}

		const auto total_sum = std::accumulate(coins_.begin(), coins_.end(), static_cast<T>(0));
		const auto half_total = total_sum / 2;

		const auto coin = [this](std::size_t i) { return coins_[i]; };
		const auto half_fairest = knapsack_max_value(n, half_total, coin, coin);
		const auto min_diff = total_sum - 2 * half_fairest;

		std::cout << min_diff << '\n';
	}

private:
	std::vector<T> coins_;
};

int main()
{
	Dividing_coins p;
	return p.run();
}

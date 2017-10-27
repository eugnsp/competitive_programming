/*********************************************************************
Dividing coins
--------------
UVa ID: 562

Goal:	determine the most fair division of a collection
		of coins between two persons.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_zero_one_knapsack.hpp"
#include <cstddef>
#include <vector>
#include <numeric>
#include <iostream>
#include <cassert>

class Dividing_coins : public CP1
{
private:
	using T = unsigned int;

private:
	virtual void read_input() override
	{
		// <number of coins>
		// <coin_1> <coin_n>

		std::cin >> n_coins_;

		coins_.resize(n_coins_);
		for (auto& c : coins_)
			std::cin >> c;
	}

	virtual void solve(std::size_t) override
	{
		if (n_coins_ == 0)
		{
			std::cout << "0\n";
			return;
		}

		const auto total_sum = std::accumulate(coins_.begin(), coins_.end(), static_cast<T>(0));
		const auto half_total = total_sum / 2;

		const auto coin = [this](std::size_t i) { return coins_[i]; };
		const auto half_fairest = knapsack_max_value(n_coins_, half_total, coin, coin);
		const auto min_diff = total_sum - 2 * half_fairest;

		std::cout << min_diff << '\n';
	}

private:
	std::size_t n_coins_;
	std::vector<T> coins_;
};

int main()
{
	Dividing_coins p;
	return p.run();
}

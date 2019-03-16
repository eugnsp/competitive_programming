/*********************************************************************
Dividing coins
--------------
UVa ID: 005 62

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_zero_one_knapsack.hpp"
#include <cstddef>
#include <vector>
#include <numeric>
#include <cassert>

class CP : public CP1
{
private:
	using T = unsigned int;

private:
	virtual void read_input() override
	{
		read_size_vec(coins_);
	}

	virtual void solve(unsigned int) override
	{
		const auto total_sum = std::accumulate(coins_.begin(), coins_.end(), static_cast<T>(0));
		const auto half_total = total_sum / 2;

		const auto coin = [this](std::size_t i) { return coins_[i]; };
		const auto half_fairest = knapsack_max_value(n_coins_, half_total, coin, coin);
		const auto min_diff = total_sum - 2 * half_fairest;

		write_ln(min_diff);
	}

	virtual void end() override
	{
		write_ln(0);
	}

private:
	std::size_t n_coins_;
	std::vector<T> coins_;
};



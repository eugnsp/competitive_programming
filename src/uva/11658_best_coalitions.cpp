/*********************************************************************
Best coalitions
---------------
UVa ID: 116 58

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_zero_one_knapsack.hpp"
#include <cstddef>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <iomanip>
#include <cassert>

class CP : public CP2
{
private:
	using T = unsigned int;
	static constexpr T total_shares = 10000;

private:
	virtual bool read_input() override
	{
		std::size_t n_stockholders;
		if (!read(n_stockholders, target_stockholder_) ||
			(n_stockholders == 0 && target_stockholder_ == 0))
			return false;

		assert(0 < target_stockholder_ && target_stockholder_ <= n_stockholders);
		--target_stockholder_; // To zero-based indexing

		shares_.resize(n_stockholders);
		std::generate_n(shares_.begin(), shares_.size(), [] {
			double share;
			read(share);
			return static_cast<T>(std::round(100 * share));
		});

		assert(std::accumulate(shares_.begin(), shares_.end(), static_cast<T>(0)) == total_shares);
		return true;
	}

	virtual void solve(unsigned int) override
	{
		const auto n = shares_.size() - 1;
		const auto target_share = shares_[target_stockholder_];
		shares_.erase(shares_.begin() + target_stockholder_);

		// To get the maximum profit we should exclude stockholders with highest shares,
		// but not too many of them (their total share should be less than 50%)
		const auto share = [this](std::size_t i) { return shares_[i]; };
		const auto excluded_shares = knapsack_max_value(n, (total_shares - 1) / 2, share, share);
		const auto best_share =
			static_cast<double>(target_share) / (total_shares - excluded_shares);

		write_ln(std::fixed, std::setprecision(2), 100 * best_share);
	}

private:
	std::size_t target_stockholder_;
	std::vector<T> shares_;
};



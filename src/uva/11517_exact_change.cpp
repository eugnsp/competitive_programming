/*********************************************************************
Exact change
------------
UVa ID: 115 17

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_coin_change.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <vector>

class CP : public CP1
{
private:
	using T = unsigned int;
	static constexpr T max_price = 10000;
	static constexpr std::size_t max_n_coins = 100;

private:
	virtual void read_input() override
	{
		read(price_);
		assert(price_ <= max_price);

		read_size_vec(coins_);
	}

	virtual void solve(unsigned int) override
	{
		constexpr auto max_amount_to_pay = 2 * max_price;
		const auto change = zero_one_coin_change(coins_, max_amount_to_pay);

		auto amount_paid = price_;
		while (change[amount_paid].n > max_n_coins)
		{
			++amount_paid;
			assert(amount_paid <= max_amount_to_pay);
		}

		write_ln(amount_paid, ' ', change[amount_paid].n);
	}

private:
	T price_;
	std::vector<T> coins_;
};

MAIN

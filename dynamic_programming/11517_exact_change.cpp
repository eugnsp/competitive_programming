/*********************************************************************
Exact change
------------
UVa ID: 11517

Goal:	find the best combination of coins to pay at least as much
		as the given value.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_coin_change.hpp"
#include <cstddef>
#include <vector>
#include <algorithm>
#include <iterator>
#include <iostream>
#include <cassert>

class Exact_change : public CP1
{
private:
	using T = unsigned int;
	static constexpr T max_price = 10000;
	static constexpr std::size_t max_n_coins = 100;

private:
	virtual void read_input() override
	{
		// <price>
		// <number of coins = n>
		// <denomination_1>
		// ... 
		// <denomination_n>

		std::size_t n;

		std::cin >> price_ >> n;
		assert(price_ <= max_price);
		assert(n <= max_n_coins);

		coins_.resize(n);
		std::copy_n(std::istream_iterator<T>(std::cin), coins_.size(), coins_.begin());
	}

	virtual void solve(std::size_t) override
	{
		constexpr auto max_amount_to_pay = 2 * max_price;
		const auto change = zero_one_coin_change(coins_, max_amount_to_pay);

		auto amount_paid = price_;
		while (change[amount_paid].n > max_n_coins)
		{
			++amount_paid;
			assert(amount_paid <= max_amount_to_pay);
		}

		std::cout << amount_paid << ' ' << change[amount_paid].n << '\n';
	}

private:
	T price_;
	std::vector<T> coins_;
};

int main()
{
	Exact_change p;
	return p.run();
}

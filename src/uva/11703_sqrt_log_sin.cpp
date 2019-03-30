/*********************************************************************
sqrt log sin
------------
UVa ID: 117 03

A sequence is defined by the following recurrence:
	x_0 = 1,
	x_i = x_⌊i - sqrt(p)i⌋ + x_⌊ln(i)⌋ + x_⌊i * sin^2(i)⌋.

Input
-----

ue of i, no less than zero and no greater than one million. Input
is
e is not a value of i and should not be processed.

Output
------
For each value of i in the input (but not the final "-1"), output the
corresponding value of x_i modulo 1'000'000.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <vector>

constexpr auto mod = 1'000'000u;
constexpr auto max_i = 1'000'000u;

template<typename S, typename T, typename U>
void compute_xi(std::vector<unsigned int>& x, unsigned int i, S s, T t, U u)
{
	x[i] = x[static_cast<std::size_t>(s)] + x[static_cast<std::size_t>(t)] +
		   x[static_cast<std::size_t>(u)];
	if (x[i] > mod)
		x[i] %= mod;
}

std::vector<unsigned int> compute_x()
{
	constexpr unsigned int small_exp = 9;

	std::vector<unsigned int> x(max_i + 1);
	x[0] = 1;

	unsigned int i = 1;
	const auto max = std::min(max_i, static_cast<unsigned int>(std::exp(small_exp)));
	for (; i <= max; ++i)
		compute_xi(x, i, i - std::sqrt(i), std::log(i), i * std::sin(i) * std::sin(i));

	const auto max_exp = static_cast<unsigned int>(std::log(max_i));
	for (auto exp = small_exp; exp <= max_exp; ++exp)
	{
		const auto max = std::min(max_i, static_cast<unsigned int>(std::exp(exp + 1)));
		for (; i <= max; ++i)
			compute_xi(x, i, i - std::sqrt(i), exp, i * std::sin(i) * std::sin(i));
	}

	return x;
}

class CP : public CP2
{
private:
	virtual void init() override
	{
		x_ = compute_x();
	}

	virtual bool read_input() override
	{
		int i;
		if (!read(i) || i < 0)
			return false;

		i_ = static_cast<unsigned int>(i);
		return true;
	}

	virtual void solve(unsigned int) override
	{
		write_ln(x_[i_]);
	}

private:
	std::vector<unsigned int> x_;
	unsigned int i_;
};

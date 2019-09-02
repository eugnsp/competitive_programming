/*********************************************************************
Kahan summation algorithm
-------------------------

Create a binary search tree from the given a sorted array. If there
are n elements in the array, then floor(n/2)-th element should be
chosen as the root.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <utility>
#include <type_traits>
#include <iomanip>
#include <limits>

template<class T, class Fn>
auto plain_sum(T n0, T n1, Fn fn)
{
	std::invoke_result_t<Fn, T> sum = 0;
	for (auto n = n0; n <= n1; ++n)
		sum += fn(n);

	return sum;
}

template<class T, class Fn>
auto kahan_sum(T n0, T n1, Fn fn)
{
	std::invoke_result_t<Fn, T> sum = 0;
	std::invoke_result_t<Fn, T> carry = 0;
	for (auto n = n0; n <= n1; ++n)
	{
		const auto y = fn(n) - carry;
		const auto t = sum + y;
		carry = (t - sum) - y;
		sum = t;
	}

	return sum;
}

template<typename T>
auto fn(T n)
{
	return 1 / (n * n);
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(n_);
	}

	virtual void solve(unsigned int) override
	{
		write(std::setprecision(std::numeric_limits<float>::digits10 + 1));
		write_ln(plain_sum(1, n_, [](auto n) { return fn<float>(n); }));

		write(std::setprecision(std::numeric_limits<double>::digits10 + 1));
		write_ln(plain_sum(1, n_, [](auto n) { return fn<double>(n); }));

		write(std::setprecision(std::numeric_limits<float>::digits10 + 1));
		write_ln(kahan_sum(1, n_, [](auto n) { return fn<float>(n); }));

		write(std::setprecision(std::numeric_limits<double>::digits10 + 1));
		write_ln(kahan_sum(1, n_, [](auto n) { return fn<double>(n); }));

		write_ln();
	}

private:
	int n_;
};

MAIN

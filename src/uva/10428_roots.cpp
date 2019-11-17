/*********************************************************************
The roots
---------
UVa ID: 104 28

A polynomial equation has the following form:
	a_n x^n + a_{n-1} x^{n-1} + ... + a_1 x^1 + a_0 = 0.
Here x is variable and a_i are known as coefficient. So to specify
a polynomial equation we need the values of the coefficients only.
The roots of a polynomial equation are the values of x for which the
value of LHS is zero. In this problem you will have to find the roots
of a polynomial equation. You can assume that a polynomial equation
of degree n should have n real roots and all the roots are strictly
different.

Input
-----
The input file contains less than 5001 lines of input. Each line
contains an integer N (N <= 5) followed by (N + 1) floating point
numbers. Here N is the order of the polynomial equation. The next
(N + 1) numbers denote the values of an, ..., a0. These absolute
values of these coefficients will be less than 1e9 and the absolute
values of the roots will be less than 25. So each line contains
information about one polynomial equation. Input is terminated
by a line where N = 0.

Output
------
For each line of input produce one line of output. This line starts
with the string "Equation S:", here S is the output serial number.
This string is followed by N floating point numbers, which are the
roots of the corresponding input equation. The roots should be printed
in ascending order of their values and rounded up to four digits
after the decimal point. All the root values are preceded by a single
space. The judge input is designed in such a way that if your precision
is relatively low (values less than 1e-10 are considered as zero) you
will face no precision errors. Of course your solution must be correct
and you must be well aware of the limitations of different root finding
methods.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <array>
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <optional>
#include <type_traits>

constexpr double tol = 1e-5;
constexpr double x_max = 25;
constexpr double x_min = -x_max;
constexpr std::size_t n_max = 5;

template<class It, class Fn>
void for_each_pair(It first, It last, Fn&& fn)
{
	assert(first != last);
	auto next = std::next(first);
	while (next != last)
		fn(*first++, *next++);
}

// Finds the root of the equation fn(x) = 0 with a monotonic function fn(x)
// at the interval [left, right]
template<typename T, class Fn>
std::optional<T> find_root(T left, T right, Fn&& fn, T tol)
{
	if (std::signbit(fn(left)) == std::signbit(fn(right)))
		return {};

	auto left_sign = std::signbit(fn(left));
	while (right - left > tol)
	{
		const auto mid = (left + right) / 2;
		const auto mid_sign = std::signbit(fn(mid));
		if (left_sign == mid_sign)
		{
			left = mid;
			left_sign = mid_sign;
		}
		else
			right = mid;
	}

	return left;
}

template<typename T, std::size_t n>
std::array<T, n - 1> derivative(std::array<T, n> an)
{
	static_assert(n > 0, "n should be positive");
	std::array<T, n - 1> dn;
	for (std::size_t i = 1; i < n; ++i)
		dn[i - 1] = an[i - 1] * (n - i);
	return dn;
}

// Finds the root of the equation a[0] x^{n-1} + a[1] x^{n-2} + ... + a[n - 1] = 0
// at the interval [left, right]; calls output(xi) for each root xi in the ascending order
template<typename T, std::size_t n, class Output_fn>
void find_roots(const std::array<T, n>& an, T left, T right, Output_fn output)
{
	// Computes fn(x) = a[0] x^{n-1} + a[1] x^{n-2} + ... + a[n - 1] using the Horner's method
	const auto fn = [&an](T x) { return std::accumulate(an.begin(), an.end(), T{0},
		[x](T y, T a) { return a + y * x; }); };

	if constexpr (n > 0)
	{
		std::array<T, n + 1> d_roots;
		auto d_roots_it = d_roots.begin();
		*d_roots_it++ = left;
		find_roots(derivative(an), left, right, [&](T xi) { *d_roots_it++ = xi; });
		*d_roots_it++ = right;

		for_each_pair(d_roots.begin(), d_roots_it, [&output, &fn](T l, T r)
		{
			if (const auto xi = find_root(l, r, fn, tol); xi)
				output(*xi);
		});
	}
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		if (!read(n_) || n_ == 0)
			return false;

		for (std::size_t i = 0; i <= n_; ++i)
			read(an_[i]);
		return true;
	}

	virtual void solve(unsigned int i_case) override
	{
		write(std::fixed, std::setprecision(4), "Equation ", i_case, ':');
		solve(std::integral_constant<std::size_t, n_max>{});
	}

	template<std::size_t n>
	void solve(std::integral_constant<std::size_t, n>)
	{
		if (n == n_)
		{
			std::array<double, n + 1> an;
			std::copy_n(an_.begin(), n + 1, an.begin());

			find_roots(an, x_min, x_max, [](double xi) { write(' ', xi); });
			write_ln();
		}
		if constexpr (n >= 2)
			solve(std::integral_constant<std::size_t, n - 1>{});
	}

private:
	std::array<double, n_max + 1> an_;
	std::size_t n_;
};

MAIN

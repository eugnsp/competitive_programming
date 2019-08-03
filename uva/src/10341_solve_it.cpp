/*********************************************************************
Solve it
--------
UVa ID: 103 41

Solve the equation:
	p exp(-x) + q sin(x) + r cos(x) + s tan(x) + t x^2 + u = 0,
where 0 <= x <= 1.

Input
-----
Input consists of multiple test cases and terminated by an EOF. Each
test case consists of 6 integers in a single line: p, q, r, s, t,
and u (where 0 <= p, r <= 20 and -20 <= q, s, t <= 0). There will be
maximum 2100 lines in the input file.

Output
------
For each set of input, there should be a line containing the value
of x, correct up to 4 decimal places, or the string "No solution",
whichever is applicable.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <optional>

template<class Fn, class Dfn>
std::optional<double> solve_newton(Fn fn, Dfn dfn, double x, double eps, unsigned int max_iter = 100)
{
	for (unsigned int it = 0; it < max_iter; ++it)
	{
		const auto f = fn(x);
		if (std::abs(f) < eps)
			return x;
		const auto df = dfn(x);
		x -= f / df;
	}

	return {};
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(p_, q_, r_, s_, t_, u_);
	}

	virtual void solve(unsigned int) override
	{
		const auto fn = [this](double x) {
			return p_ * std::exp(-x) + q_ * std::sin(x) + r_ * std::cos(x) + s_ * std::tan(x) + t_ * x * x + u_;
		};
		const auto dfn = [this](double x) {
			const auto cos = std::cos(x);
			return -p_ * std::exp(-x) + q_ * cos - r_ * std::sin(x) + s_ / (cos * cos) + 2 * t_ * x;
		};

		const auto eps = 1e-4;
		const auto y = solve_newton(fn, dfn, .5, eps / 100);
		if (y)
		{
			const auto val = *y;
			if (val >= -eps && val <= 1 + eps)
			{
				write_ln(std::fixed, std::setprecision(4), std::clamp(val, 0., 1.));
				return;
			}
		}

		write_ln("No solution");
	}

private:
	double p_, q_, r_, s_, t_, u_;
};

MAIN

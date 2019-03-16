/*********************************************************************
Modular Fibonacci
-----------------
UVa ID: 102 29

The Fibonacci numbers (0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, ...) are
defined by the recurrence:
	F0 = 0
	F1 = 1
	Fi = F_{i-1} + F_{i-2} for i >1
Write a program which calculates Mn = Fn mod 2^m for given pair of
n and m, 0 <= n <= 2147483647 and 0 <= m < 20.

Input
-----
Input consists of several lines specifying a pair of n and m.

Output
------
Output should be corresponding Mn, one per line.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <array>

using T = unsigned long;
using Matrix = std::array<T, 4>;

void operator*=(Matrix& x, Matrix y)
{
	const auto a = x[0];
	const auto b = x[1];
	const auto c = x[2];
	const auto d = x[3];

	x[0] = a * y[0] + c * y[1];
	x[1] = b * y[0] + d * y[1];
	x[2] = a * y[2] + c * y[3];
	x[3] = b * y[2] + d * y[3];
}

Matrix matrix_power(Matrix m, T exp)
{
	Matrix r{1, 0, 0, 1};
	while (exp != 0)
	{
		if (exp & 1u)
			r *= m;
		m *= m;
		exp >>= 1;
	}

	return r;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(n_, m_);
	}

	virtual void solve(unsigned int) override
	{
		if (n_ <= 1)
			write_ln(n_);
		else
		{
			const auto m = matrix_power({0, 1, 1, 1}, n_ - 1);
			write_ln(m[3] % (1u << m_));
		}
	}

private:
	unsigned long n_;
	unsigned int m_;
};



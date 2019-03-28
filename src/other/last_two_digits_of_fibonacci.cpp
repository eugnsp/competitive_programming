/*********************************************************************
Last two digits of Fibonacci
----------------------------

For the given integer n find the last two digits of the n-th Fibonacci
number.

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

	x[0] = (a * y[0] + c * y[1]) % 100;
	x[1] = (b * y[0] + d * y[1]) % 100;
	x[2] = (a * y[2] + c * y[3]) % 100;
	x[3] = (b * y[2] + d * y[3]) % 100;
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

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(n_);
	}

	virtual void solve(unsigned int) override
	{
		if (n_ <= 1)
			write_ln(n_);
		else
		{
			const auto m = matrix_power({0, 1, 1, 1}, n_ - 1);
			write_ln(m[3] % 100);
		}
	}

private:
	unsigned long n_;
};



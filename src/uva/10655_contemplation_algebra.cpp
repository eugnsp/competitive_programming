/*********************************************************************
Contemplation! Algebra
----------------------
UVa ID: 106 55

Given the value of a + b and a * b you will have to find the value
of a^n + b^n.

Input
-----
The input file contains several lines of inputs. Each line except the
last line contains 3 non-negative integers p, q and n. Here p denotes
the value of a + b and q denotes the value of a * b. Input is
terminated by a line containing only two zeroes. This line should not
be processed. Each number in the input file fits in a signed 32-bit
integer. There will be no such input so that you have to find the
value of 0^0.

Output
------
For each line of input except the last one produce one line of output.
This line contains the value of a^n + b^n. You can always assume that
a^n + b^n fits in a signed 64-bit integer.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cstddef>

template<class Matrix, typename Exp>
Matrix power(Matrix x, Exp exp)
{
	assert(x.rows() == x.cols());

	Matrix res(x.rows(), x.rows(), 0);
	for (typename Matrix::Size i = 0; i < res.rows(); ++i)
		res(i, i) = 1;

	while (exp != 0)
	{
		if (exp & 1u)
			res = res * x;

		x = x * x;
		exp >>= 1;
	}

	return res;
}

using T = long long;

// Returns (a^n + b^n) given (p = a + b) and (q = ab)
T a_to_nth_p_b_to_nth(T p, T q, T n)
{
	// f(n) = a^n + b^n = p * (a^{n - 1} + b^{n - 1}) - q * (a^{n - 2} + b^{n - 2})
	// The recurrence relation: f(n) = p * f(n - 1) - q * f(n - 2).
	// The base case: f(0) = 2 and f(1) = p.

	const T f[] = {2, p};
	if (n <= 1)
		return f[n];

	Matrix<T> r(2, 2);
	r(0, 0) = p;
	r(0, 1) = -q;
	r(1, 0) = 1;
	r(1, 1) = 0;

	r = power(r, n - 1);
	return f[1] * r(0, 0) + f[0] * r(0, 1);
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(p_, q_, n_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(a_to_nth_p_b_to_nth(p_, q_, n_));
	}

private:
	T p_;
	T q_;
	T n_;
};

MAIN(CP)

/*********************************************************************
Contemplation! Algebra
----------------------
UVa ID: 106 55

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"

using T = long long;

// Returns (a^n + b^n) given (p = a + b) and (q = ab)
T a_to_nth_p_b_to_nth(T p, T q, T n)
{
	// f(n) = a^n + b^n = p * (a^{n - 1} + b^{n - 1}) - q * (a^{n - 2} + b^{n - 2})
	//
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

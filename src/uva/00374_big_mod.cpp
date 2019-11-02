/*********************************************************************
Big mod
-------
UVa ID: 003 74

Calculate R = B^P mod M for large values of B, P, and M using an
efficient algorithm.

Input
-----
The input will contain several test cases, each of them as described
below. Consecutive test cases are separated by a single blank line.
Three integer values (in the order B, P, M) will be read one number
per line. B and P are integers in the range 0 to 2'147'483'647
inclusive. M is an integer in the range 1 to 46340 inclusive.

Output
------
For each test, the result of the computation. A single integer on a
line by itself.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"

template<typename T>
T mod_exp(T base, T mod, unsigned int exp)
{
	base %= mod;

	T r = 1;
	while (exp)
	{
		if (exp & 1u)
			r = (r * base) % mod;
		base = (base * base) % mod;
		exp >>= 1;
	}
	return r;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(base_, exp_, mod_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(mod_exp(base_, mod_, exp_));
	}

private:
	unsigned int base_, exp_, mod_;
};

MAIN

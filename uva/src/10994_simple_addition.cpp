/*********************************************************************
Simple addition
---
UVa ID: 109 94

Lets define a simple recursive function F(n), where
	       / n % 10      if (n % 10) > 0,
	F(n) = | 0           if n = 0,
           \ F(n / 10)   otherwise.
Let's define another function S(p, q) = sum_{i = p}^q F(i).
In this problem you have to calculate S(p, q) on given values
of p and q.

Input
-----
The input file contains several lines of inputs. Each line contains
two non-negative integers p and q (p <= q) separated by a single
space. p and q will fit in 32 bit signed integer. Input is terminated
by a line which contains two negative integers. This line should not
be processed.

Output
------
For each set of input print a single line of the value of S(p, q).

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"

// Returns S(0, n)
unsigned long long sum(unsigned long n)
{
	// Partial sums 0 + 1 + ... + k.
	constexpr unsigned int partial_sums[10] = {0, 1, 3, 6, 10, 15, 21, 28, 36, 45};

	unsigned long long s = 0;
	for (; n > 0; n /= 10)
		s += (n / 10) * partial_sums[9] + partial_sums[n % 10];

	return s;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		long p, q;
		if (!read(p, q) || p < 0 || q < 0)
			return false;

		p_ = static_cast<unsigned long>(p);
		q_ = static_cast<unsigned long>(q);
		return true;
	}

	virtual void solve(unsigned int) override
	{
		write_ln(sum(q_) - (p_ == 0 ? 0 : sum(p_ - 1)));
	}

private:
	unsigned long p_, q_;
};

MAIN

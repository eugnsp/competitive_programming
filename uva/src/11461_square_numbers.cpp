/*********************************************************************
Square numbers
--------------
UVa ID: 114 61

A square number is an integer number whose square root is also an
integer. For example 1, 4, 81 are some square numbers. Given two
numbers a and b, you will have to find out how many square numbers
are there between a and b  (inclusive).

Input
-----
The input file contains at most 201 lines of inputs. Each line contains
two integers a and b (0 < a <= b <= 100'000). Input is terminated by
a line containing two zeroes. This line should not be processed.

Output
------
For each line of input produce one line of output. This line contains
an integer which denotes how many square numbers are there between
a and b (inclusive).

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>

template<typename T>
T floor_sqrt(const T x)
{
	assert(x >= 0);

	T left = 0;
	T right = static_cast<T>(1) << (4 * sizeof(x));

	// Loop invariants: left ^ 2 <= x, (right + 1) ^ 2 > x

	while (left < right)
	{
		const auto mid = (left + right + 1) / 2;
		if (mid * mid <= x)
			left = mid;
		else
			right = mid - 1;
	}

	return left;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(a_, b_) && a_ > 0 && b_ > 0;
	}

	virtual void solve(unsigned int) override
	{
		write_ln(floor_sqrt(b_) - floor_sqrt(a_ - 1));
	}

private:
	unsigned int a_, b_;
};



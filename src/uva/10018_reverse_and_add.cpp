/*********************************************************************
Reverse and add
---------------
UVa ID: 100 18

The "reverse and add" method is simple: choose a number, reverse its
digits and add it to the original. If the sum is not a palindrome
(which means, it is not the same number from left to right and right
to left), repeat this procedure. This method leads to palindromes in
a few step for almost all of the integers. But there are interesting
exceptions. 196 is the first number for which no palindrome has been
found. It is not proven though, that there is no such a palindrome.
You must write a program that give the resulting palindrome and the
number of iterations (additions) to compute the palindrome. You might
assume that all tests data on this problem:
	* will have an answer,
	* will be computable with less than 1000 iterations (additions),
	* will yield a palindrome that is not greater than 4'294'967'295.

Input
-----
The first line will have a number N (0 < N <= 100) with the number
of test cases, the next N lines will have a number P to compute its
palindrome.

Output
------
For each of the N tests you will have to write a line with the
following data:
<minimum number of iterations> <the resulting palindrome>

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>

template<typename T>
T reverse(T x)
{
	assert(x > 0);
	T rx = 0;
	for (; x > 0; x /= 10)
		rx = 10 * rx + x % 10;
	return rx;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(x_);
	}

	virtual void solve(unsigned int) override
	{
		unsigned int n = 0;
		while (true)
		{
			const auto rx = reverse(x_);
			if (n > 0 && rx == x_)
				break;
			x_ += rx;
			++n;
		}

		write_ln(n, ' ', x_);
	}

private:
	unsigned int x_;
};

MAIN

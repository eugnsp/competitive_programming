/*********************************************************************
Just the facts
--------------
UVa ID: 005 68

The expression N! denotes the product of the first N positive integers,
where N is nonnegative. For this problem, you are to write a program
that can compute the last non-zero digit of any factorial for N,
0 <= N <= 10'000. For example, if your program is asked to compute
the last nonzero digit of 5!, your program should produce "2" because
5! = 120, and 2 is the last nonzero digit of 120.

Input
-----
Input to the program is a series of nonnegative integers not exceeding
10'000, each on its own line with no other letters, digits or spaces.
For each integer N, you should read the value and compute the last
nonzero digit of N!.

Output
------
For each integer input, the program should print exactly one line of
output. Each line of output should contain the value N, right-justified
in columns 1 through 5 with leading blanks, not leading zeroes.
Columns 6-9 must contain " -> ". Column 10 must contain the single last
non-zero digit of N!.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <iomanip>

template<typename T>
unsigned int last_non_zero_digit_of_factorial(const T n)
{
	// http://math.stackexchange.com/questions/130352/last-non-zero-digit-of-a-factorial
	assert(n >= 0);

	const unsigned int last_digits[10] = {1, 1, 2, 6, 4, 2, 2, 4, 2, 8};
	if (n < 10)
		return last_digits[n];

	const auto f1 = last_non_zero_digit_of_factorial(n / 5);
	const auto f2 = last_digits[n % 10];
	const auto f3 = 2 * (3 - (n / 10) % 2);

	return (f1 * f2 * f3) % 10;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(n_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(std::setw(5), n_, " -> ", last_non_zero_digit_of_factorial(n_));
	}

private:
	unsigned int n_;
};

MAIN

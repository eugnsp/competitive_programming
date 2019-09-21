/*********************************************************************
The archeologists' dilemma
--------------------------
UVa ID: 007 01

An archeologist seeking proof of the presence of extraterrestrials in
the Earth's past, stumbles upon a partially destroyed wall containing
strange chains of numbers. The left-hand part of these lines of digits
is always intact, but unfortunately the right-hand one is often lost
by erosion of the stone. However, she notices that all the numbers with
all its digits intact are powers of 2, so that the hypothesis that
all of them are powers of 2 is obvious. To reinforce her belief, she
selects a list of numbers on which itis apparent that the number of
legible digits is strictly smaller than the number of lost ones, and
asks you to find the smallest power of 2 (if any) whose first digits
coincide with those of the list. Thus you must write a program such
that given an integer, it determines (if it exists) the smallest
exponent E such that the first digits of 2^E coincide with the integer
(remember that more than half of the digits are missing).

Input
-----
It is a set of lines with a positive integer N not bigger than
2'147'483'648 in each of them.

Output
------
For every one of these integers a line containing the smallest
positive integer E such that the first digits of 2^E are precisely
the digits of N, or, if there is no one, the sentence "no power of 2".

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <cmath>

// Returns the minimum power (e) of 2, such that first digits
// of (2^e) are equal to (n), and the total number of digits
// of (2^e) is greater than twice the number of digits of (n)
unsigned int power_of_two_with_first_digits(unsigned int n)
{
	const auto log2_10 = std::log2(10);
	const auto log2_n = std::log2(n);
	const auto log2_np1 = std::log2(n + 1);
	const auto n_digits = static_cast<unsigned int>(std::log10(n)) + 1;
	auto m = n_digits + 1;

	while (true)
	{
		// Note: n1 and n2 before cast are never exact integers
		const auto n1 = static_cast<unsigned int>(m * log2_10 + log2_n);
		const auto n2 = static_cast<unsigned int>(m * log2_10 + log2_np1);
		if (n1 < n2)
			return n2;
		++m;
	}

	assert(false);
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
		write_ln(power_of_two_with_first_digits(n_));
	}

private:
	unsigned int n_;
};

MAIN


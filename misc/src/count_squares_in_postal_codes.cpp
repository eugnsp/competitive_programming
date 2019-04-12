/*********************************************************************
Count squares in postal codes
-----------------------------

Count the total number of squares in all numbers from zero up to the
given one. The digits 6 and 9 have one square, the digit 8 has two
squares, other digits have no squares.

# # #      #  # # #  # # #  #   #  # # #      #  # # #  # # #  # # #
#   #    # #      #    #    #   #  #        #      #    #   #  #   #
#   #  #   #      #  # # #  # # #  # # #  # # #  #      # # #  # # #
#   #      #    #      #        #      #  #   #  #      #   #    #
# # #      #  # # #  #          #  # # #  # # #  #      # # #  #

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>

unsigned long long ten_to_n(unsigned int exp)
{
	unsigned long long ten_to_n = 1;
	unsigned long long base = 10;
	while (exp)
	{
		if (exp & 1u)
			ten_to_n *= base;
		base *= base;
		exp >>= 1;
	}
	return ten_to_n;
}

// Counts squares for a
unsigned int count_a(const unsigned int a)
{
	assert(a <= 9);
	return (a == 6) + 2u * (a == 8) + (a == 9);
}

// Counts squares in the range [0, a]
unsigned int count_below_a(const unsigned int a)
{
	assert(a <= 9);
	return (a >= 6) + 2u * (a >= 8) + (a >= 9);
}

// Counts squares in the range [000...0, 999...9] with n total digits
unsigned long long count_below_999(const unsigned int n)
{
	return (n == 0) ? 0 : 4 * n * ten_to_n(n - 1);
}

// Counts squares in the range [000...0, a99...9] with n + 1 total digits
unsigned long long count_below_a99(const unsigned int a, const unsigned int n)
{
	assert(0 < a && a <= 9);
	return (a + 1) * count_below_999(n) + ten_to_n(n) * count_below_a(a);
}

unsigned long long count(const unsigned int num)
{
	if (num <= 9)
		return count_below_a(num);

	unsigned int n = 0;
	auto a = num;
	while (a >= 10)
	{
		++n;
		a /= 10;
	}

	assert(0 < a && a <= 9);
	const auto res = num - a * ten_to_n(n);

	if (a > 1)
		return count_below_a99(a - 1, n) + count_a(a) * (res + 1) + count(res);
	else
		return count_below_999(n) + count(res);
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
		write_ln(count(n_));
	}

private:
	unsigned int n_;
};

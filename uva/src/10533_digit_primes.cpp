/*********************************************************************
Digit primes
------------
UVa ID: 105 33

A prime number is a positive number, which is divisible by exactly
two different integers. A digit prime is a prime number whose sum of
digits is also prime. For example the prime number 41 is a digit prime
because 4 + 1 = 5 and 5 is a prime number. 17 is not a digit prime
because 1 + 7 = 8, and 8 is not a prime number. In this problem your
job is to find out the number of digit primes within a certain range
less than 1'000'000.

Input
-----
First line of the input file contains a single integer N
(0 < N <= 500'000) that indicates the total number of inputs.
Each of the next N lines contains two integers t1 and t2
(0 < t1 <= t2 < 1'000'000).

Output
------
For each line of input except the first line produce one line of
output containing a single integer that indicates the number of digit
primes between t1 and t2 (inclusive).

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <cmath>
#include <cstddef>
#include <vector>

static constexpr auto max_n = 1'000'000u;

std::vector<bool> generate_prime_flags(std::size_t max)
{
	std::vector<bool> is_prime(max + 1, true);

	is_prime[0] = is_prime[1] = false;
	for (std::size_t i = 4; i <= max; i += 2)
		is_prime[i] = false;

	const auto sqrt_max = static_cast<std::size_t>(std::sqrt(max));
	for (std::size_t i = 3; i <= sqrt_max; i += 2)
		if (is_prime[i])
			for (auto j = i * i; j <= max; j += 2 * i)
				is_prime[j] = false;

	return is_prime;
}

class CP : public CP1
{
private:
	virtual void init() override
	{
		const auto prime_flags = generate_prime_flags(max_n);
		n_digit_primes_.resize(max_n);

		unsigned int n = 0;
		for (unsigned int i = 0; i < max_n; ++i)
		{
			if (prime_flags[i])
			{
				auto x = i;
				unsigned int digits_sum = 0;
				while (x > 0)
				{
					digits_sum += x % 10;
					x /= 10;
				}
				if (prime_flags[digits_sum])
					++n;
			}
			n_digit_primes_[i] = n;
		}
	}

	virtual void read_input() override
	{
		read(t1_, t2_);
		assert(0 < t1_ && t1_ <= t2_ && t2_ < max_n);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(n_digit_primes_[t2_] - n_digit_primes_[t1_ - 1]);
	}

private:
	unsigned int t1_, t2_;
	std::vector<unsigned int> n_digit_primes_;
};



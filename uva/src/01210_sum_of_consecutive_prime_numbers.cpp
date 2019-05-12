/*********************************************************************
Sum of consecutive prime numbers
--------------------------------
UVa ID: 1210

Some positive integers can be represented by a sum of one or more
consecutive prime numbers. How many such representations does a given
positive integer have? For example, the integer 53 has two
representations 5 + 7 + 11 + 13 + 17 and 53. The integer 41 has three
representations 2 + 3 + 5 + 7 + 11 + 13, 11 + 13 + 17, and 41. The
integer 3 has only one representation, which is 3. The integer 20 has
no such representations. Note that summands must be consecutive prime
numbers, so neither 7 + 13 nor 3 + 5 + 5 + 7 is a valid representation
for the integer 20. Your mission is to write a program that reports
the number of representations for the given positive integer.

Input
-----
The input is a sequence of positive integers each in a separate line.
The integers are between 2 and 10'000, inclusive. The end of the input
is indicated by a zero.

Output
------
The output should be composed of lines each corresponding to an input
line except the last zero. An output line includes the number of
representations for the input integer as the sum of one or more
consecutive prime numbers. No other characters should be inserted
in the output.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <cmath>
#include <cstddef>
#include <vector>

static constexpr auto max_n = 10'000u;

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

template<typename T>
std::vector<T> generate_primes(T max)
{
	std::vector<T> primes;
	if (max < 2)
		return primes;

	primes.push_back(2);
	const auto is_prime = generate_prime_flags(max);
	for (T i = 3; i <= max; i += 2)
		if (is_prime[i])
			primes.push_back(i);

	return primes;
}

class CP : public CP2
{
private:
	virtual void init() override
	{
		primes_ = generate_primes(max_n);
	}

	virtual bool read_input() override
	{
		return read(n_) && n_ != 0;
	}

	virtual void solve(unsigned int) override
	{
		std::size_t n_ways = 0;
		unsigned int sum = 0;

		for (auto head = primes_.begin(), tail = head; tail != primes_.end() && *tail <= n_; ++tail)
		{
			sum += *tail;
			while (sum > n_)
			{
				assert(head < tail);
				sum -= *head++;
			}

			if (sum == n_)
				++n_ways;
		}

		write_ln(n_ways);
	}

private:
	unsigned int n_;
	std::vector<unsigned int> primes_;
};

MAIN


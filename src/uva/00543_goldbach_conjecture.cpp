/*********************************************************************
Goldbach's conjecture
---------------------
UVa ID: 005 43

In 1742, Christian Goldbach, a German amateur mathematician, sent a
letter to Leonhard Euler in which he made the following conjecture:
	Every number greater than 2 can be written
	as the sum of three prime numbers.
Goldbach was considering 1 as a primer number, a convention that is
no longer followed. Later on, Euler re-expressed the conjecture as:
	Every even number greater than or equal to 4
	can be expressed as the sum of two prime numbers.
Today it is still unproven whether the conjecture is right. Anyway,
your task is now to verify Goldbach's conjecture as expressed by
Euler for all even numbers less than a million.

Input
-----
The input file will contain one or more test cases. Each test case
consists of one even integer n with 6 <= n < 1'000'000. Input will
be terminated by a value of 0 for n.

Output
------
For each test case, print one line of the form n = a + b, where
a and b are odd primes. Numbers and operators should be separated by
exactly one blank like in the sample output below. If there is more
than one pair of odd primes adding up to n, choose the pair where the
difference b - a is maximized. If there is no such pair, print a line
saying "Goldbach's conjecture is wrong.".

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cstddef>
#include <cmath>
#include <vector>

constexpr std::size_t max_n = 1'000'000u;

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

class CP : public CP2
{
private:
	virtual void init() override
	{
		prime_flags_ = generate_prime_flags(max_n);
	}

	virtual bool read_input() override
	{
		return read(n_) && n_ != 0;
	}

	virtual void solve(unsigned int) override
	{
		for (std::size_t i = 3; i <= n_ / 2; i += 2)
			if (prime_flags_[i] && prime_flags_[n_ - i])
			{
				write_ln(n_, " = ", i, " + ", n_ - i);
				return;
			}

		write_ln("Goldbach's conjecture is wrong."); 	// O'RLY? ;)
	}

private:
	std::size_t n_;
	std::vector<bool> prime_flags_;
};



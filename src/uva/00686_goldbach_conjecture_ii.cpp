/*********************************************************************
Goldbach's conjecture II
------------------------
UVa ID: 686

Goldbach's Conjecture:
	For any even number n greater than or equal to 4, there exists at
	least one pair of prime numbers p1 and p2 such that n = p1 + p2.
This conjecture has not been proved nor refused yet. No one is sure
whether this conjecture actually holds. However, one can find such a
pair of prime numbers, if any, for a given even number. The problem
here is to write a program that reports the number of all the pairs of
prime numbers satisfying the condition in the conjecture for a given
even number. A sequence of even numbers is given as input.
Corresponding to each number, the program should output the number of
pairs mentioned above. Notice that we are interested in the number of
essentially different pairs and therefore you should not count
(p1, p2) and (p2, p1) separately as two different pairs.

Input
-----
An integer is given in each input line. You may assume that each
integer is even, and is greater than or equal to 4 and less than 2^15.
The end of the input is indicated by a number 0.

Output
------
Each output line should contain an integer number. No other characters
should appear in the output.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cmath>
#include <cstddef>
#include <vector>

constexpr std::size_t max_n = (2u << 14);

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
		std::size_t n = 0;
		for (std::size_t i = 2; i <= n_ / 2; ++i)
			if (prime_flags_[i] && prime_flags_[n_ - i])
				++n;

		write_ln(n);
	}

private:
	std::size_t n_;
	std::vector<bool> prime_flags_;
};



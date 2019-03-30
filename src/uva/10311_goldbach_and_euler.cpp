/*********************************************************************
Goldbach and Euler
------------------
UVa ID: 103 11

  That every number which is resolvable into two prime numbers can be
  resolved into as many prime numbers as you like, can be illustrated
  and confirmed by an observation which you have formerly communicated
  to me, namely that every even number is a sum of two primes, and
  since n - 2) is also a sum of two prime numbers, n must be a sum of
  three, and also four prime numbers, and so on. If, however, n is an
  odd number, then it is certainly a sum of three prime numbers, since
  n - 1) is a sum of two prime numbers, and can therefore be resolved
  into as many prime numbers as you like. However, that every number
  is a sum of two primes, I consider a theorem which is quite true,
  although I cannot demonstrate it.
  							Euler to Goldbach, 1742
The above conjecture about all numbers being the sum of two primes
(where 1 counts as a prime) is not always true, but it is more true
for even numbers. Your task is to test the conjecture for specified
integers, considering that prime numbers are the numbers which are
positive and divisible by exactly two positive integers. Your program
must be very efficient.

Input
-----
The input file contains 100'000 lines of input. Each line contains
a single integer n (0 < n <= 100'000'000). Input is terminated by
end of file.

Output
------
For each line of input produce one line of output. This line should
be of one of the following types: n is not the sum of two primes!
n is the sum of p1 and p2. For the second case, always make sure
that (p2 <= p1) is positive and minimized.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <cmath>
#include <cstddef>
#include <vector>

static constexpr auto max_n = 100'000'000u;

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
		return read(n_);
	}

	virtual void solve(unsigned int) override
	{
		if (n_ > 1 && n_ % 2 == 1)
		{
			if (prime_flags_[n_ - 2])
			{
				write_ln(n_, " is the sum of 2 and ", n_ - 2, '.');
				return;
			}
		}
		else
		{
			for (auto i = (n_ - 1) / 2; i > 0; --i)
				if (prime_flags_[i] && prime_flags_[n_ - i])
				{
					write_ln(n_, " is the sum of ", i, " and ", n_ - i, '.');
					return;
				}
		}

		write_ln(n_, " is not the sum of two primes!");
	}

private:
	unsigned int n_;
	std::vector<bool> prime_flags_;
};



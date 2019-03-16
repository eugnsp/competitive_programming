/*********************************************************************
Goldbach and Euler
------------------
UVa ID: 103 11

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "primes.hpp"
#include <vector>
#include <cassert>

class CP : public CP2
{
private:
	using T = unsigned int;
	static constexpr T max_n = 100000000;

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
	T n_;
	std::vector<bool> prime_flags_;
};



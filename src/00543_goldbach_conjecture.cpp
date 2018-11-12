/*********************************************************************
Goldbach's conjecture
---------------------
UVa ID: 543

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
	static constexpr T max_n = 1000000;

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
		for (T i = 3; i <= n_ / 2; i += 2)
			if (prime_flags_[i] && prime_flags_[n_ - i])
			{
				write_ln(n_, " = ", i, " + ", n_ - i);
				return;
			}

		write_ln("Goldbach's conjecture is wrong.");	// O'RLY? ;)
	}

private:
	T n_;
	std::vector<bool> prime_flags_;
};

MAIN(CP)

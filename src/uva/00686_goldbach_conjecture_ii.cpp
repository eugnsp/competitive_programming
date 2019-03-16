/*********************************************************************
Goldbach's conjecture II
------------------------
UVa ID: 686

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
	static constexpr T max_n = (2u << 14);

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
		T n = 0;
		for (T i = 2; i <= n_ / 2; ++i)
			if (prime_flags_[i] && prime_flags_[n_ - i])
				++n;

		write_ln(n);
	}

private:
	T n_;
	std::vector<bool> prime_flags_;
};



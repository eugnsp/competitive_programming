/*********************************************************************
Digit primes
------------
UVa ID: 105 33

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <vector>

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
	using T = unsigned int;
	static constexpr T max_n = 1000000;

private:
	virtual void init() override
	{
		const auto prime_flags = generate_prime_flags(max_n);
		n_digit_primes_.resize(max_n);

		T n = 0;
		for (T i = 0; i < max_n; ++i)
		{
			if (prime_flags[i])
			{
				auto x = i;
				T digits_sum = 0;
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
	T t1_, t2_;
	std::vector<T> n_digit_primes_;
};



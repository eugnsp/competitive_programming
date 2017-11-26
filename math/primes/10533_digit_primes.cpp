/*********************************************************************
Digit primes
------------
UVa ID: 10533

Goal:	find the number of digit primes (a prime, such that the sum
		of its digits is also prime) inside the given range.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "primes.hpp"
#include <cassert>
#include <vector>

class Digit_primes : public CP1
{
private:
	using T = unsigned int;
	static constexpr T max_prime = 1000000;

private:
	virtual void init() override
	{
		const auto prime_flags = generate_prime_flags(max_prime);
		n_digit_primes_.resize(max_prime);

		T n = 0;
		for (T i = 0; i < max_prime; ++i)
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

	virtual void read_input(std::istream& in) override
	{
		// <t1> <t2>

		in >> t1_ >> t2_;
		assert(0 < t1_ && t1_ <= t2_ && t2_ < max_prime);
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		out << n_digit_primes_[t2_] - n_digit_primes_[t1_ - 1] << '\n';
	}

private:
	T t1_, t2_;
	std::vector<T> n_digit_primes_;
};

int main()
{
	Digit_primes p;
	return p.run();
}

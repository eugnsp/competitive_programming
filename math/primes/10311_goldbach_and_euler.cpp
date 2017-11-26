/*********************************************************************
Goldbach and Euler
------------------
UVa ID: 10311

Goal:	determine if the given number can be represented as a sum
		of two distinct prime numbers.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "primes.hpp"
#include <vector>
#include <cassert>

class Goldbach_Euler : public CP2
{
private:
	using T = unsigned int;
	static constexpr T max_prime = 100000000;

private:
	virtual void init() override
	{
		prime_flags_ = generate_prime_flags(max_prime);
	}

	virtual bool read_input(std::istream& in) override
	{
		// <n>

		in >> n_;
		if (!in)
			return false;

		assert(0 < n_ && n_ <= max_prime);
		return true;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		if (n_ > 1 && n_ % 2 == 1)
		{
			if (prime_flags_[n_ - 2])
			{
				out << n_ << " is the sum of 2 and " << n_ - 2 << ".\n";
				return;
			}
		}
		else
		{
			for (auto i = (n_ - 1) / 2; i > 0; --i)
				if (prime_flags_[i] && prime_flags_[n_ - i])
				{
					out << n_ << " is the sum of " << i << " and " << n_ - i << ".\n";
					return;
				}
		}

		out << n_ << " is not the sum of two primes!\n";
	}

private:
	T n_;
	std::vector<bool> prime_flags_;
};

int main()
{
	Goldbach_Euler p;
	return p.run();
}

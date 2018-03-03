/*********************************************************************
Goldbach's conjecture II
------------------------
UVa ID: 686

Goal:	find the number of ways the given even number can be
		represented as a sum of two prime numbers.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "primes.hpp"
#include <vector>
#include <cassert>

class Goldbach : public CP2
{
private:
	using T = unsigned int;
	static constexpr T max_n = (2u << 14);

private:
	virtual void init() override
	{
		prime_flags_ = generate_prime_flags(max_n);
	}

	virtual bool read_input(std::istream& in) override
	{
		// <n>

		in >> n_;
		if (n_ == 0)
			return false;

		assert(4 <= n_ && n_ <= max_n && n_ % 2 == 0);
		return true;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		T n = 0;
		for (T i = 2; i <= n_ / 2; ++i)
			if (prime_flags_[i] && prime_flags_[n_ - i])
				++n;

		out << n << '\n';
	}

private:
	T n_;
	std::vector<bool> prime_flags_;
};

int main()
{
	Goldbach p;
	return p.run();
}

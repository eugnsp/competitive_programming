/*********************************************************************
Goldbach's conjecture
---------------------
UVa ID: 543

Goal:	verify the Goldbach's conjecture as expressed by Euler
		for all even numbers less than a million.

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
	static constexpr T max_prime = 1000000;

private:
	virtual void init() override
	{
		prime_flags_ = generate_prime_flags(max_prime);
	}

	virtual bool read_input(std::istream& in) override
	{
		// <n>

		in >> n_;
		if (n_ == 0)
			return false;

		assert(6 <= n_ && n_ <= max_prime && n_ % 2 == 0);
		return true;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		for (T i = 3; i <= n_ / 2; i += 2)
			if (prime_flags_[i] && prime_flags_[n_ - i])
			{
				out << n_ << " = " << i << " + " << n_ - i << '\n';
				return;
			}

		out << "Goldbach's conjecture is wrong.\n";		// ORLY? ;)
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

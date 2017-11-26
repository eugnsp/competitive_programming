/*********************************************************************
Count the factors
-----------------
UVa ID: 10699

Goal:	find the number of different prime factors
		in a positive integer.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "primes.hpp"
#include <cassert>

class Count_factors : public CP2
{
private:
	using T = unsigned int;

private:
	virtual bool read_input(std::istream& in) override
	{
		// <n>

		in >> n_;
		if (n_ == 0)
			return false;

		assert(n_ <= 1000000);
		return true;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		const auto factors = factorize(n_);
		out << n_ << " : " << factors.size() << '\n';
	}

private:
	T n_;
};

int main()
{
	Count_factors p;
	return p.run();
}

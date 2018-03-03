/*********************************************************************
Prime factors
-------------
UVa ID: 583

Goal:	find prime factors of the given number.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "primes.hpp"
#include <cassert>
#include <utility>

class Prime_factors : public CP2
{
private:
	using T = int;

private:
	virtual bool read_input(std::istream& in) override
	{
		// <n>

		in >> n_;
		return (n_ != 0);
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		const auto factors = factorize(n_ > 0 ? n_ : -n_);
		out << n_ << " = ";
		if (n_ < 0)
			out << "-1 x ";

		for (auto f = factors.begin(); f != factors.end(); ++f)
		{
			if (f != factors.begin())
				out << " x ";
			out << f->first;
			for (unsigned int exp = 1; exp < f->second; ++exp)
				out << " x " << f->first;
		}
		out << '\n';
	}

private:
	T n_;
};

int main()
{
	Prime_factors p;
	return p.run();
}
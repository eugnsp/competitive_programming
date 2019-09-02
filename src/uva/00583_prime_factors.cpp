/*********************************************************************
Prime factors
-------------
UVa ID: 005 83

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "primes.hpp"
#include <cassert>
#include <utility>

class CP : public CP2
{
private:
	using T = int;

private:
	virtual bool read_input() override
	{
		return read(n_) && n_ != 0;
	}

	virtual void solve(unsigned int) override
	{
		const auto factors = factorize(n_ > 0 ? n_ : -n_);
		write(n_, " = ");
		if (n_ < 0)
			write("-1 x ");

		for (auto f = factors.begin(); f != factors.end(); ++f)
		{
			if (f != factors.begin())
				write(" x ");
			write(f->first);
			for (unsigned int exp = 1; exp < f->second; ++exp)
				write(" x ", f->first);
		}
		write_ln();
	}

private:
	T n_;
};

MAIN


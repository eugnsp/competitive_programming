/*********************************************************************
Count the factors
-----------------
UVa ID: 106 99

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "primes.hpp"
#include <cassert>

class CP : public CP2
{
private:
	using T = unsigned int;

private:
	virtual bool read_input() override
	{
		return read(n_) && n_ != 0;
	}

	virtual void solve(unsigned int) override
	{
		const auto factors = factorize(n_);
		write_ln(n_, " : ", factors.size());
	}

private:
	T n_;
};



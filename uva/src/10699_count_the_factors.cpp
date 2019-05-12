/*********************************************************************
Count the factors
-----------------
UVa ID: 106 99

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <cmath>
#include <utility>
#include <vector>

template<typename T>
T get_smallest_factor(T x)
{
	if (x % 2 == 0)
		return 2;

	const auto sqrt_x = static_cast<T>(std::sqrt(x));
	for (T i = 3; i <= sqrt_x; i += 2)
		if (x % i == 0)
			return i;

	return x;
}

template<typename T>
std::vector<std::pair<T, unsigned int>> factorize(T x)
{
	assert(x > 1);

	std::vector<std::pair<T, unsigned int>> factors;
	while (x > 1)
	{
		const auto base = get_smallest_factor(x);
		unsigned int exp = 0;
		do
		{
			x /= base;
			++exp;
		} while (x % base == 0);

		factors.push_back({base, exp});
	}

	return factors;
}

class CP : public CP2
{
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
	unsigned int n_;
};

MAIN


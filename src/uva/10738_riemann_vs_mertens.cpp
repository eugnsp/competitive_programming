/*********************************************************************
Riemann vs Mertens
------------------
UVa ID: 107 38

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "primes.hpp"
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <numeric>
#include <vector>

class CP : public CP2
{
private:
	using T = int;
	static constexpr T max_n = 1000000;

private:
	virtual void init() override
	{
		mobius_.resize(max_n + 1);

		mobius_[0] = 0;
		mobius_[1] = 1;
		for (T i = 2; i <= max_n; ++i)
		{
			const auto factors = factorize(i);
			if (std::all_of(
					factors.begin(), factors.end(), [](const std::pair<T, unsigned int>& f) {
						return f.second == 1;
					}))
			{
				mobius_[i] = (factors.size() % 2 == 0) ? 1 : -1;
			}
			else
				mobius_[i] = 0;
		}

		mertens_.resize(max_n + 1);
		std::partial_sum(mobius_.begin(), mobius_.end(), mertens_.begin());
	}

	virtual bool read_input() override
	{
		return read(n_) && n_ != 0;
	}

	virtual void solve(unsigned int) override
	{
		write_ln(std::setw(8), n_, std::setw(8), mobius_[n_], std::setw(8), mertens_[n_]);
	}

private:
	T n_;
	std::vector<T> mobius_;
	std::vector<T> mertens_;
};

MAIN(CP)
/*********************************************************************
Divisors
--------
UVa ID: 002 94

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "primes.hpp"
#include <cassert>
#include <utility>

class CP : public CP1
{
private:
	using T = unsigned long long;

private:
	virtual void read_input() override
	{
		read(lower_, upper_);

		assert(1 <= lower_ && lower_ <= 1000000000);
		assert(lower_ <= upper_);
		assert(upper_ - lower_ <= 10000);
	}

	virtual void solve(unsigned int) override
	{
		std::pair<T, T> answer(0, 0);
		for (T i = lower_; i <= upper_; ++i)
		{
			const auto factors = factorize(i);

			T n_factors = 1;
			for (auto& f : factors)
				n_factors *= f.second + 1;

			if (n_factors > answer.second)
				answer = {i, n_factors};
		}

		write_ln(
			"Between ",
			lower_,
			" and ",
			upper_,
			", ",
			answer.first,
			" has a maximum of ",
			answer.second,
			" divisors.");
	}

private:
	T lower_;
	T upper_;
};



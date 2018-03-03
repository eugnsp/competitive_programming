/*********************************************************************
Riemann vs Mertens
------------------
UVa ID: 10738

Goal:	compute Mobius and Mertens functions.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "primes.hpp"
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <numeric>
#include <vector>

class Riemann_vs_Mertens : public CP2
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
			if (std::all_of(factors.begin(), factors.end(),
				[](const std::pair<T, unsigned int>& f)
			{
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

	virtual bool read_input(std::istream& in) override
	{
		// <n>

		in >> n_;
		if (n_ == 0)
			return false;

		assert(1 <= n_ && n_ <= max_n);
		return true;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		out << std::setw(8) << n_ << std::setw(8) << mobius_[n_]
			<< std::setw(8) << mertens_[n_] << '\n';
	}

private:
	T n_;
	std::vector<T> mobius_;
	std::vector<T> mertens_;
};

int main()
{
	Riemann_vs_Mertens p;
	return p.run();
}

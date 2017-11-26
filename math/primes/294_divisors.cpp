/*********************************************************************
Divisors
--------
UVa ID: 294

Goal:	inside the given range find the number which has the largest
		number of divisors.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "primes.hpp"
#include <cassert>
#include <utility>

class Divisors : public CP1
{
private:
	using T = unsigned long long;

private:
	virtual void read_input(std::istream& in) override
	{
		// <lower bound> <upper bound>

		in >> lower_ >> upper_;

		assert(1 <= lower_ && lower_ <= 1000000000);
		assert(lower_ <= upper_);
		assert(upper_ - lower_ <= 10000);
	}

	virtual void solve(std::ostream& out, std::size_t) override
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

		out << "Between " << lower_ << " and " << upper_ << ", " << answer.first
			<< " has a maximum of " << answer.second << " divisors.\n";
	}

private:
	T lower_;
	T upper_;
};

int main()
{
	Divisors p;
	return p.run();
}
/*********************************************************************
Dropping water balloons
-----------------------
UVa ID: 10934

Goal:	find the minimum number of trials in order to determine
		the lowest floor from which you can drop a balloon
		so that it bursts.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <vector>
#include <algorithm>
#include <cassert>

class Baloons : public CP2
{
	using T = unsigned long long;

private:
	virtual bool read_input(std::istream& in) override
	{
		// <number of baloons> <number of floors>

		in >> n_baloons_ >> n_floors_;
		if (n_baloons_ == 0)
			return false;

		assert(1 <= n_baloons_ && n_baloons_ <= 100);
		assert(n_floors_ > 0);
		return true;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		/*********************************************************************
		mf(b, t) is the maximum number of floors that can be reached
					with (b) baloons and (t) trials.

		The recurrence relation:
			mf(b, t) = mf(b - 1, t - 1) + 1 + mf(b, t - 1).

		The base case:
			mf(b, 0) = mf(0, t) = 0 for all (b) and (t).
		**********************************************************************/

		std::vector<T> mf(n_baloons_ + 1, 0);

		for (std::size_t n_tries = 2; n_tries < 64; ++n_tries)
		{
			for (std::size_t i = n_baloons_; i > 0; --i)
				mf[i] = mf[i] + mf[i - 1] + 1;

			assert(mf[n_baloons_] < static_cast<T>(-1) / 2);
			if (mf[n_baloons_ - 1] + 1 + mf[n_baloons_] >= n_floors_)
			{
				out << n_tries << '\n';
				return;
			}
		}

		out << "More than 63 trials needed.\n";
	}

private:
	T n_floors_;
	std::size_t n_baloons_;
};

int main()
{
	Baloons p;
	return p.run();
}

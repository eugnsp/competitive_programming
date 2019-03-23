/*********************************************************************
Square root
-----------

For the given the integer find the floor of the square root of it.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>

template<typename T>
T floor_sqrt(const T x)
{
	assert(x >= 0);

	T left = 0;
	T right = static_cast<T>(1) << (4 * sizeof(x));

	// Loop invariant: left ^ 2 <= x, (right + 1) ^ 2 > x
	// At the beginning: left = 0, right = max. possible value of sqrt
	// At the end: left = right = floor(sqrt(x))

	while (left != right)
	{
		auto mid = (left + right + 1) / 2;
		if (mid * mid <= x)
			left = mid;
		else
			right = mid - 1;
	}

	return left;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(x_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(floor_sqrt(x_));
	}

private:
	unsigned int x_;
};



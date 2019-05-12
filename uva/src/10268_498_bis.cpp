/*********************************************************************
498-bis
-------
UVa ID: 102 68

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <vector>

using T = int;

// Returns the derivative of the polynomial (as) at the point (x)
T derivative(const std::vector<T>& as, T x)
{
	T d = 0;
	const auto end = as.end() - 1;
	for (auto it = as.begin(); it != end; ++it)
		d = d * x + *it * static_cast<T>(end - it);

	return d;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		as_.clear();
		return read(x_) && read_vec_ln(as_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(derivative(as_, x_));
	}

private:
	std::vector<T> as_;
	T x_;
};

MAIN


/*********************************************************************
498-bis
-------
UVa ID: 102 68

In 498 you had to evaluate the values of polynomial
	a_0 x^n + a_1 x^{n - 1} + ... + a_{n - 1} x + a_n.
In this problem you should evaluate its derivative. Remember that
derivative is defined as
	a_0 n * x^{n - 1} + a_1 (n - 1) x^{n - 2} + ... + a_{n - 1}.
All the input and output data will fit into integer, i.e. its
absolute value will be less than 2^31.

Input
-----
Your program should accept an even number of lines of text. Each pair
of lines will represent one problem. The first line will contain one
integer - a value for x. The second line will contain a list of
integers {a0, a1, ..., an}, which represent a set of polynomial
coefficients. Input is terminated by <EOF>.

Output
------
For each pair of lines, your program should evaluate the derivative
of polynomial for the given value x and output it in a single line.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <vector>

template<class It, typename T>
T derivative(It first, const It last, const T x)
{
	auto dp = T{0};
	if (first == last)
		return dp;

	auto an = *first;
	while (++first != last)
	{
		dp = dp * x + an * static_cast<T>(last - first);
		an = *first;
	}

	return dp;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		if (!read(x_))
			return false;

		as_.clear();
		ignore_line();
		read_vec_ln(as_);
		return true;
	}

	virtual void solve(unsigned int) override
	{
		write_ln(derivative(as_.begin(), as_.end(), x_));
	}

private:
	std::vector<long long> as_;
	long long x_;
};

MAIN

/*********************************************************************
Number of paths in a grid
-------------------------

Find the number of paths in a (N x M)-grid for the given N and M.
Paths are constrained: from the cell (i, j) one can jump to
the cells (i + 1, j) or (i, j + 1).

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <vector>

template<typename T>
unsigned long long binomial_coeff(T n, T k)
{
	if (n < k)
		return 0;
	if (k > n - k)
		k = n - k;

	unsigned long long b = 1;
	for (T i = 1; i <= k; ++i)
	{
		b *= n--;
		b /= i;
	}

	return b;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(n_, m_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(binomial_coeff(n_ + m_ - 2, m_ - 1));
	}

private:
	unsigned int n_, m_;
};

MAIN

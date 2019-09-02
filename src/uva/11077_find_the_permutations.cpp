/*********************************************************************
Find the permutations
---------------------
UVa ID: 110 77

Sorting is one of the most used operations in real life, where
Computer Science comes into act. It is well-known that the lower bound
of swap based sorting is n log(n). It means that the best possible
sorting algorithm will take at least O(nlog(n)) swaps to sort a set of
n integers. However, to sort a particular array of n integers, you can
always find a swapping sequence of at most (n -1) swaps, once you know
the position of each element in the sorted sequence. For example
consider four elements <1 2 3 4>. There are 24 possible permutations
and for all elements you know the position in sorted sequence. If the
permutation is <2 1 4 3>, it will take minimum 2 swaps to make it
sorted. If the sequenceis <2 3 4 1>, at least 3 swaps are required.
The sequence <4 2 3 1> requires only 1 and the sequence <1 2 3 4>
requires none. In this way, we can find the permutations of N distinct
integers which will take at least K swaps to be sorted.

Input
-----
Each input consists of two positive integers N(1 <= N <= 21) and
K (0 <= K < N) in a single line. Input is terminated by two zeros.
There can be at most 250 test cases.

Output
------
For each of the input, print in a line the number of permutations
which will take at least K swaps.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cassert>

// Returns the Stirling number of the 1st find
unsigned long long stirling_1st(const unsigned int n, const unsigned int k)
{
	assert(k <= n);

	if (k == n)
		return 1;
	if (k == 0)
		return 0;

	Matrix<unsigned long long> st(n + 1, k + 1, 0);
	for (unsigned int i = 0; i < std::min(n + 1, k + 1); ++i)
		st(i, i) = 1;

	for (unsigned int j = 0; j <= k; ++j)
		for (unsigned int i = j + 1; i <= n; ++i)
		{
			st(i, j) = (i - 1) * st(i - 1, j);
			if (j > 0)
				st(i, j) += st(i - 1, j - 1);
		}

	return st(n, k);
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(n_, n_swaps_) && n_ != 0;
	}

	virtual void solve(unsigned int) override
	{
		write_ln(stirling_1st(n_, n_ - n_swaps_));
	}

private:
	unsigned int n_;
	unsigned int n_swaps_;
};

MAIN


/*********************************************************************
Chest of drawers
----------------
UVa ID: 114 20

A chest of drawers means a wardrobe which has many drawers aligned
vertically. Although this is useful furniture, some problems arise
when all the drawers need have provisions of locking - that is
sometimes a drawer is not secured even if it is locked. For example
assume that the third drawer from the top is locked but the drawer
immediately above it is not locked. Then the drawer that is locked is
also not secured because one can access it by pulling out the drawer
immediately above it. In a chest of n drawers, there are a number of
ways to ensure that exactly s drawers are secure. Given the value of
n and s, your job is to find out in how many ways they can be secured.

Input
-----
The input file contains at most 5000 lines of inputs. Each line
contains two integers n and s ( 1 <= n <= 65 and 0 <= s <= 65). Here
n is the total number of drawers and s is the number of drawers that
needs to be secured. Input is terminated by a line containing two
negative numbers. This input should not be processed.

Output
------
For each line of input produce one line of output. This line contains
an integer which denotes in how many ways s drawers out of the n drawers,
can be secured.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cassert>
#include <utility>

unsigned long long count_secure(const unsigned int n_total, const unsigned int n_secured)
{
	if (n_total < n_secured)
		return 0;
	if (n_total <= n_secured + 1)
		return 1;

	assert(n_total > n_secured + 1);

	// `n_ways(i, j)` is the number of ways to secure `j` drawers out of `i + 1` drawers:
	// `.first` if the first drawer is unlocked, `.second` if the first drawer is locked
	Matrix<std::pair<unsigned long long, unsigned long long>>
		n_ways(n_total, n_total + 1, {0, 0});

	n_ways(0, 0).first = n_ways(0, 1).second = 1;
	for (unsigned int i = 1; i < n_total; ++i)
		n_ways(i, i + 1).second = n_ways(i, i).second = 1;

	for (unsigned int i = 1; i < n_total; ++i)
		for (unsigned int j = 0; j < i; ++j)
		{
			n_ways(i, j).first = n_ways(i - 1, j).first + n_ways(i - 1, j + 1).second;
			if (j > 0)
				n_ways(i, j).second = n_ways(i - 1, j - 1).first + n_ways(i - 1, j - 1).second;
		}

	return n_ways(n_total - 1, n_secured).first + n_ways(n_total - 1, n_secured).second;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		int n_total, n_secured;
		if (!read(n_total, n_secured) || n_total < 0 || n_secured < 0)
			return false;

		n_total_ = static_cast<unsigned int>(n_total);
		n_secured_ = static_cast<unsigned int>(n_secured);
		return true;
	}

	virtual void solve(unsigned int) override
	{
		write_ln(count_secure(n_total_, n_secured_));
	}

private:
	unsigned int n_total_;
	unsigned int n_secured_;
};



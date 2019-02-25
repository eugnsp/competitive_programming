/*********************************************************************
Handshakes
----------
URL: https://practice.geeksforgeeks.org/problems/handshakes/0

We have N persons sitting on a round table. Any person can do a
handshake with any other person. Example:
   1
2     3
   4
Handshake with 2-3 and 1-4 will cause cross. In how many ways these
N people can make handshakes so that no two handshakes crosses each
other? N would be even. For example, in above diagram, there are two
non-crossing ways to handshake {{1, 2}, {3, 4}} and {{1, 3}, {2, 4}}.

Input
-----
The first line of input contains an integer T denoting the number
of test cases. The first line of each test case is N.

Output
------
Print number of ways.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <vector>
#include <utility>

unsigned int n_handshakes(unsigned int n_pairs)
{
	static std::vector<unsigned int> memo{1, 1, 2};
	if (n_pairs < memo.size())
		return memo[n_pairs];

	unsigned int n = n_handshakes(n_pairs - 1);

	for (unsigned int left = 0; left < n_pairs - 1; ++left)
		for (unsigned int right = left; right < n_pairs - 1; ++right)
		{
			n += n_handshakes(left) * n_handshakes(right - left) * n_handshakes(n_pairs - 2 - right);
		}

	memo.resize(n_pairs + 1);
	memo[n_pairs] = n;
	return n;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(n_pairs_);
		n_pairs_ /= 2;
	}

	virtual void solve(unsigned int) override
	{
		write_ln(n_handshakes(n_pairs_));
	}

private:
	unsigned int n_pairs_;
};

MAIN(CP)

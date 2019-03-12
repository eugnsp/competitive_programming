/*********************************************************************
Safe salutations
----------------
UVa ID: 009 91

As any minimally superstitious person knows all too well, terrible
things will happen when four persons do a crossed handshake. You, an
intrepid computer scientist, are given the task of easing the burden
of these people by providing them with the feasible set of handshakes
that include everyone in the group while avoiding any such crossings.

Input
-----
The input to this problem contains several datasets separated by a
blank line. Each dataset is simply an integer n, the number of pairs
of people in the group, with 1 <= n <= 10.

Output
------
The output is equally simple. For each dataset, print a single integer
indicating the number of possible crossless handshakes that involve
everyone in a group with n pairs of people. Print a blank line between
datasets.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cstddef>
#include <vector>

std::size_t count_handshakes(std::size_t n_pairs)
{
	std::vector<std::size_t> catalan(n_pairs + 1);
	catalan[0] = 1;
	catalan[1] = 1;
	catalan[2] = 2;

	for (std::size_t i = 3; i <= n_pairs; ++i)
	{
		catalan[i] = catalan[i - 1];
		for (std::size_t left = 0; left < i - 1; ++left)
			for (auto right = left; right < i - 1; ++right)
				catalan[i] += catalan[left] * catalan[right - left] * catalan[i - 2 - right];
	}

	return catalan.back();
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(n_pairs_);
	}

	virtual void solve(unsigned int i_case) override
	{
		if (i_case > 0)
			write_ln();

		write_ln(count_handshakes(n_pairs_));
	}

private:
	std::size_t n_pairs_;
};

MAIN(CP)

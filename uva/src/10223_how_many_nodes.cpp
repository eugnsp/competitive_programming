/*********************************************************************
How many nodes?
---------------
UVa ID: 102 23

One of the most popular topic of Data Structures is Rooted Binary
Tree. If you are given some nodes you can definitely able to make the
maximum number of trees with them. But if you are given the maximum
number of trees built upon a few nodes, can you find out how many
nodes built those trees?

Input
-----
The input file will contain one or more test cases. Each test case
consists of an integer n (n <= 4'294'967'295). Here n is the maximum
number of trees.

Output
------
For each test case, print one line containing the actual number of
nodes.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cstddef>
#include <vector>

std::size_t count_nodes(std::size_t n_trees)
{
	if (n_trees <= 2)
		return n_trees;

	std::vector<std::size_t> catalan{1, 1, 2};
	while (true)
	{
		const auto n = catalan.size() - 1;

		std::size_t c = 0;
		for (std::size_t i = 0; i <= n; ++i)
			c += catalan[i] * catalan[n - i];

		if (c >= n_trees)
			return n + 1;

		catalan.push_back(c);
	}
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(n_trees_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(count_nodes(n_trees_));
	}

private:
	std::size_t n_trees_;
};

MAIN


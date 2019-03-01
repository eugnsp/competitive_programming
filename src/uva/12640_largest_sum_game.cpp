/*********************************************************************
Largest sum game
----------------
UVa ID: 126 40

After a long beer party and when ready for the check, John and his
friends play the largest sum game and whoever wins the game will not
have to pay a dime of the check. The largest sum game consists in
finding the largest sum of consecutive values in a sequence of
numbers; the winner is the one quickest to answer.

For example, in the sequence {23, -1, -24, 2, 23} the largest sum of
consecutive values is 25 and whoever finds this value first, is the
winner of the game.

Although simple (and geeky), the game is challenging because beer and
arithmetic do not mix well together. However, since the group of
friends are amateur programmers, each have implemented an algorithmic
solution for finding the largest sum and have agreed to select the
winner of the game in the form of a programming challenge: they
connect their laptops to a central server that produces a random
sequence of numeric values, run the solutions on this data, and the
program quickest to answer wins the game.

John is tired of paying night after night without ever winning the
game and he is determined to stop this situation tonight. John has
hired you to write a highly efficient computer program that could beat
the others in the largest sum game.

Input
-----
The input consists of several test cases, each one de ned by a line
containing a sequence of N blank-separated integers X_1, X_2, ... X_N,
(1 <= N <= 10^5, -10^3 <= X_i <= 10^3 for each 1 <= i <= N).

Output
------
For each test case, output a line with the largest sum of consecutive
values in X_1, X_2, ...,  X_N.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

using T = int;

// Returns the sum of contiguous subarray within
// the array [first, last) which has the largest sum
template<class It, typename T = typename std::iterator_traits<It>::value_type>
T kadane_max_sum(It first, It last)
{
	assert(first != last);

	auto max_sum = *first++;
	for (auto sum = max_sum; first != last; ++first)
	{
		if (sum >= 0)
			sum += *first;
		else
			sum = *first;

		max_sum = std::max(max_sum, sum);
	}

	return max_sum;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		numbers_.clear();
		return read_vec_ln(numbers_);
	}

	virtual void solve(unsigned int) override
	{
		const auto sum = kadane_max_sum(numbers_.begin(), numbers_.end());
		write_ln(sum > 0 ? sum : 0);
	}

private:
	std::vector<T> numbers_;
};

MAIN(CP)

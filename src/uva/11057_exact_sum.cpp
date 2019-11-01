/*********************************************************************
Exact sum
---------
UVa ID: 110 57

Peter received money from his parents this week and wants to spend it
all buying books. But he does not read a book so fast, because he
likes to enjoy every single word while he is reading. In this way, it
takes him a week to finish a book. As Peter receives money every two
weeks, he decided to buy two books, then he can read them until
receive more money. As he wishes to spend all the money, he should
choose two books whose prices summed up are equal to the money that he
has. It is a little bit difficult to find these books, so Peter asks
your help to find them.

Input
-----
Each test case starts with 2 <= N <= 10'000, the number of available
books. Next line will have N integers, representing the price of each
book, a book costs less than 1000001. Then there is another line with
an integer M, representing how much money Peter has. There is a blank
line after each testcase. The input is terminated by end of file (EOF).

Output
------
For each test case you must print the message:
"Peter should buy books whose prices are i and j.",
where i and j are the prices of the books whose sum is equal to M and
i <= j. You can consider that is always possible to find a solution,
if there are multiple solutions print the solution that minimizes the
difference between the prices i and j. After each test case you must
print a blank line.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

template<class It, typename T>
It mid(It first, It last, const T& value)
{
	auto it =
		std::lower_bound(first, last, value, [](const T& a, const T& b) { return 2 * a < b; });

	if (it != last && 2 * *it == value)
		++it;

	return it;
}

// Returns two distinct iterators pointing at the elements in the range [first, last)
// with the given sum; if multiple pairs exist, returns the one with minimal difference
// between the elements; the range is modified
template<class It, typename T>
std::pair<It, It> find_sum(It first, It last, const T& sum)
{
	if (last - first < 2)
		return {last, last};

	std::sort(first, last);

	auto right = mid(first, last, sum);
	auto left = right;

	while (right != last && left != first)
	{
		const auto s = *right + *(left - 1);
		if (s == sum)
			return {left - 1, right};

		if (s < sum)
			++right;
		else
			--left;
	}

	return {last, last};
}

using Price = unsigned int;
using Prices = std::vector<Price>;

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_size_vec(prices_) && read(sum_);
	}

	virtual void solve(unsigned int) override
	{
		const auto prices = find_sum(prices_.begin(), prices_.end(), sum_);
		write("Peter should buy books whose prices are ");
		write_ln(*prices.first, " and ", *prices.second, '.');
		write_ln();
	}

private:
	Prices prices_;
	Price sum_;
};

MAIN

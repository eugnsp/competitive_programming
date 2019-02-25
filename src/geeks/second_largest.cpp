/*********************************************************************
Second largest
--------------

Given an array A of size N, print second largest element from an
array.

Input
-----
The first line of input contains an integer T denoting the number of
test cases. T test cases follow. Each test case contains two lines of
input. The first line contains an integer N denoting the size of the
array. The second line contains the N space seperated intgers of the
array.

Output
------
For each testcase, in a new line, print the second largest element.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <vector>

using Element = unsigned int;

template<class It>
It partition(It first, It last)
{
	if (first == last)
		return first;

	--last;
	const auto& pivot = *last;

	// [first, left):	< pivot
	// [left, right):	>= pivot
	// [right, last):	unprocessed

	auto left = first;
	for (auto right = first; right != last; ++right)
		if (*right < pivot)
			std::iter_swap(left++, right);

	std::iter_swap(left, last);
	return left;
}

// Returns the second largest element in the range [first, last),
// return last if the range contains less than two elements
template<class It>
It second_largest(It first, It last)
{
	if (last - first <= 2)
		return last;

	std::size_t k = 2;
	while (true)
	{
		auto p = partition(first, last);
		const auto n_right = static_cast<std::size_t>(last - p);
		if (n_right == k)
			return p;
		if (n_right > k)
			first = p;
		else
		{
			last = p;
			k -= n_right;
		}
	}
}

std::vector<Element>* seq;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(seq_);
	}

	virtual void solve(unsigned int) override
	{
		seq = &seq_;
		write_ln(*second_largest(seq_.begin(), seq_.end()));
	}

private:
	std::vector<Element> seq_;
};

MAIN(CP)

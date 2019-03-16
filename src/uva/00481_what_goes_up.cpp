/*********************************************************************
What goes up
------------
UVa ID: 004 81

Write a program that will select the longest strictly increasing
subsequence from a sequence of integers.

Input
-----
The input file contains a sequence of integers (positive, negative,
and/or zero). Each line of the input file will contain one integer.

Output
------
The output for this program will be a line indicating the length of
the longest subsequence, a new line, a dash character ("-"), a new
line, and then the subsequence itself printed with one integer per
line. If the input contains more than one longest subsequence, the
output file should print the one that occurs last in the input file.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <utility>
#include <vector>

// Finds the longest increasing subsequence,
// returns the last subsequence in case of a tie
template<class It>
std::vector<It> longest_inc_subsequence(It first, It last)
{
	// `fin[i]` is equal to the index `k` of the smallest value
	// `seq[k]` such that there exists a LIS of length `i + 1`
	// with the last element `seq[k]` for `k <= i`
	std::vector<It> fin;

	// Iterators to previous elements to restore the sequence
	std::vector<It> prev;
	prev.reserve(last - first);

	for (auto it = first; it != last; ++it)
	{
		const auto pos = std::lower_bound(fin.begin(), fin.end(), it,
			[](It l, It r) { return *l < *r; });

		prev.push_back(pos != fin.begin() ? *std::prev(pos) : last);

		if (pos != fin.end())
			*pos = it;
		else
			fin.push_back(it);
	}

	auto lis = fin.rbegin();	// reuse `fin` to store the result
	for (auto it = fin.back(); it != last; it = prev[it - first])
		*lis++ = it;

	return fin;
}

using T = int;

class CP : public CP3
{
private:
	virtual void read_input() override
	{
		for (T i; read(i); )
			seq_.push_back(i);
	}

	virtual void solve() override
	{
		const auto lis = longest_inc_subsequence(seq_.begin(), seq_.end());

		write_ln(lis.size());
		write_ln('-');
		for (auto it : lis)
			write_ln(*it);
	}

private:
	std::vector<T> seq_;
};



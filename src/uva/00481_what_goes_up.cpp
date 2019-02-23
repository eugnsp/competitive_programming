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
template<typename T>
std::vector<T> longest_inc_subsequence(const std::vector<T>& seq)
{
	constexpr auto invalid_index = static_cast<std::size_t>(-1);

	std::vector<std::size_t> prev(seq.size(), invalid_index);

	// `last[i]` is equal to the index `k` of the smallest value `seq[k]` such that
	// there exists a LIS of length `i + 1` with the last element `seq[k]` for `k <= i`
	std::vector<std::size_t> last;

	const auto comp = [&seq](std::size_t i, std::size_t j) { return seq[i] < seq[j]; };

	for (std::size_t i = 0; i < seq.size(); ++i)
	{
		const auto pos = std::lower_bound(last.begin(), last.end(), i, comp);

		if (pos != last.begin())
			prev[i] = *std::prev(pos);

		if (pos != last.end())
			*pos = i;
		else
			last.push_back(i);
	}

	std::vector<T> subseq;
	subseq.reserve(last.size());

	for (auto i = last.back(); i != invalid_index; i = prev[i])
		subseq.push_back(seq[i]);

	std::reverse(subseq.begin(), subseq.end());
	return subseq;
}

class CP : public CP3
{
private:
	virtual void read_input() override
	{
		decltype(seq_)::value_type i;
		while (read(i))
			seq_.push_back(i);
	}

	virtual void solve() override
	{
		const auto lis = longest_inc_subsequence(seq_);

		write_ln(lis.size());
		write_ln('-');
		write_vec(lis, '\n');
		write_ln();
	}

private:
	std::vector<int> seq_;
};

MAIN(CP)

/*********************************************************************
Sorted subsequence of size 4
----------------------------

Given an array A of N integers, find any 4 elements in it such that
A[i] < A[j] < A[k] < A[l] for i < j < k < l.

Input
-----
The first line of input contains an integer T denoting the number of
test cases. Then T test cases follow. The first line of each test case
contains an integer N denoting the size of the array A in the next
line are N space separated values of the array A.

Output
------
For each test case output three values of the sequence separated
by spaces, or "No sequence" if no such sequence exists.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <array>
#include <cstddef>
#include <utility>
#include <vector>
#include <limits>

using Element = int;

template<typename T>
std::pair<bool, std::array<T, 4>> find_seq4(const std::vector<T>& seq)
{
	T v0 = std::numeric_limits<T>::max();
	T v1 = std::numeric_limits<T>::max();
	T v2 = std::numeric_limits<T>::max();
	T v00, v000, v11;

	for (std::size_t i = 0; i < seq.size(); ++i)
		if (seq[i] <= v0)
			v0 = seq[i];
		else if (seq[i] <= v1)
		{
			v1 = seq[i];
			v00 = v0;
		}
		else if (seq[i] <= v2)
		{
			v2 = seq[i];
			v11 = v1;
			v000 = v00;
		}
		else
			return {true, {v000, v11, v2, seq[i]}};

	return {false, {}};
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(seq_);
	}

	virtual void solve(unsigned int) override
	{
		const auto seq = find_seq4(seq_);
		if (seq.first)
			write_vec(seq.second, ' ');
		else
			write("No sequence");
		write_ln();
	}

private:
	std::vector<Element> seq_;
};

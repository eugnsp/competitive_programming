/*********************************************************************
Maximum sum
-----------
UVa ID: 001 08

A problem that is simple to solve in one dimension is often much more
difficult to solve in more than one dimension.  Consider satisfying a
boolean expression in conjunctive normal form in which each conjunct
consists of exactly 3 disjuncts. This problem (3-SAT) is NP-complete.
The problem 2-SAT is solved quite efficiently, however. In contrast,
some problems belong to the same complexity class regardless of the
dimensionality of the problem.

Given a 2-dimensional array of positive and negative integers, find
the sub-rectangle with the largest sum. The sum of a rectangle is the
sum of all the elements in that rectangle. In this problem the
sub-rectangle with the largest sum is referred to as the maximal
sub-rectangle.

A sub-rectangle is any contiguous sub-array of size 1 x 1 or greater
located within the whole array.

Input
-----
The input consists of an N x N array of integers. The input begins
with a single positive integer N on a line by itself indicating the
size of the square two dimensional array. This is followed by N^2
integers separated by white-space (newlines and spaces). These N^2
integers make up the array in row-major order (i.e., all numbers on
the first row, left-to-right, then all numbers on the second row,
left-to-right, etc.). N may be as large as 100. The numbers in the
array will be in the range [-127, 127].

Output
------
The output is the sum of the maximal sub-rectangle.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <vector>

using T = int;

// Returns the sum of contiguous subarray within
// the array [first, last) which has the largest sum
template<class It, typename T = typename std::iterator_traits<It>::value_type>
T max_sum(It first, const It last)
{
	if (first == last)
		return 0;

	auto max_sum = *first++;
	for (auto sum = max_sum; first != last; ++first)
	{
		if (sum < 0)
			sum = *first;
		else
			sum += *first;

		max_sum = std::max(max_sum, sum);
	}

	return max_sum;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::size_t n;
		if (!read(n))
			return false;

		matrix.resize(n, n);
		return read_matrix(matrix);
	}

	virtual void solve(unsigned int) override
	{
		auto max = matrix(0, 0);
		std::vector<T> partial_row_sum(matrix.rows());

		for (std::size_t start_col = 0; start_col < matrix.cols(); ++start_col)
		{
			std::fill(partial_row_sum.begin(), partial_row_sum.end(), 0);
			for (auto end_col = start_col; end_col < matrix.cols(); ++end_col)
			{
				for (std::size_t j = 0; j < matrix.rows(); ++j)
					partial_row_sum[j] += matrix(j, end_col);

				const auto sum = max_sum(partial_row_sum.cbegin(), partial_row_sum.cend());
				max = std::max(max, sum);
			}
		}

		write_ln(max);
	}

private:
	Matrix<T> matrix;
};

MAIN(CP)

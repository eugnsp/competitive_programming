// Maximum sum
// -----------
//
// Goal: for a given matrix find the sub-matrix with the largest
// sum of its elements.
//
// UVa ID: 108
// This file is covered by the LICENSE file in the root of this project.

#include "../../matrix.hpp"
#include "kadane_max_sum.hpp"
#include <cstddef>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using T = int;

T max_sum_submatrix(const Matrix<T>& matrix)
{
	assert(matrix.rows() > 0 && matrix.cols() > 0);

	std::vector<T> partial_col_sum(matrix.cols());

	auto max_sum = matrix(0, 0);
	for (std::size_t start_row = 0; start_row < matrix.rows(); ++start_row)
	{
		std::fill(partial_col_sum.begin(), partial_col_sum.end(), 0);
		for (std::size_t end_row = start_row; end_row < matrix.rows(); ++end_row)
		{
			for (std::size_t j = 0; j < matrix.cols(); ++j)
				partial_col_sum[j] += matrix(end_row, j);

			const auto sum = kadane_max_sum(partial_col_sum.cbegin(), partial_col_sum.cend());
			max_sum = std::max(max_sum, sum);
		}
	}

	return max_sum;
}

// <n>
// <m_11> ... <m_1n>
// ...
// <m_n1> ... <m_nn>

int main()
{
	for (;;)
	{
		std::size_t n;
		std::cin >> n;

		if (!std::cin)
			break;

		Matrix<T> matrix(n, n);
		for (std::size_t i = 0; i < n; ++i)
			for (std::size_t j = 0; j < n; ++j)
				std::cin >> matrix(i, j);

		std::cout << max_sum_submatrix(matrix) << '\n';
	}

	return 0;
}
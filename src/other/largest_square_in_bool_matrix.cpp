/*********************************************************************
Largest square in a boolean matrix
----------------------------------

For the given binary matrix find out the maximum size of a square
sub-matrix with all 1s.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cstddef>

std::size_t largest_true_sq_submatrix(const Matrix<bool>& matrix)
{
	// dp(i, j) is the size of the largest true submatrix that has
	// the right bottom corner element matrix(i, j)
	Matrix<std::size_t> dp_matrix(matrix.rows(), matrix.cols(), 0);

	std::size_t max_size = 0;

	for (std::size_t i = 0; i < matrix.rows(); ++i)
		if (matrix(i, 0))
			max_size = dp_matrix(i, 0) = 1;
	for (std::size_t i = 1; i < matrix.cols(); ++i)
		if (matrix(0, i))
			max_size = dp_matrix(0, i) = 1;

	for (std::size_t col = 1; col < matrix.cols(); ++col)
		for (std::size_t row = 1; row < matrix.rows(); ++row)
			if (matrix(row, col))
			{
				auto& dp = dp_matrix(row, col);
				dp = 1 + std::min({dp_matrix(row - 1, col - 1),
								   dp_matrix(row - 1, col),
								   dp_matrix(row, col - 1)});

				max_size = std::max(max_size, dp);
			}

	return max_size;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t n_rows, n_cols;
		read(n_rows, n_cols);

		matrix_.resize(n_rows, n_cols);
		read_matrix<unsigned int>(matrix_, [](unsigned int i) { return i == 1; });
	}

	virtual void solve(unsigned int) override
	{
		write_ln(largest_true_sq_submatrix(matrix_));
	}

private:
	Matrix<bool> matrix_;
};



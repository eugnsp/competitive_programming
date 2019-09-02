/*********************************************************************
Matrix rotation
---------------

Rotate the given matrix by 90 degrees.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cassert>
#include <cstddef>
#include <utility>

template<typename T>
void transpose(Matrix<T>& matrix)
{
	assert(matrix.rows() == matrix.cols());
	for (std::size_t col = 0; col < matrix.cols(); ++col)
		for (std::size_t row = 0; row < col; ++row)
			std::swap(matrix(row, col), matrix(col, row));
}

template<typename T>
void flip_ud(Matrix<T>& matrix)
{
	for (std::size_t col = 0; col < matrix.cols(); ++col)
		for (std::size_t row = 0, row2 = matrix.rows() - 1; row < row2; ++row, --row2)
			std::swap(matrix(row, col), matrix(row2, col));
}

template<typename T>
void rotate(Matrix<T>& matrix)
{
	flip_ud(matrix);
	transpose(matrix);
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t size;
		read(size);
		matrix_.resize(size, size);
		read_transposed_matrix(matrix_);
	}

	virtual void solve(unsigned int) override
	{
		rotate(matrix_);
		write_range(matrix_.data().begin(), matrix_.data().end(), ' ');
		write_ln();
	}

private:
	Matrix<int> matrix_;
};

MAIN

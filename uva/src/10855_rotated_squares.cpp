/*********************************************************************
Rotated squares
---------------
UVa ID: 108 55

Given a square of N rows and columns of uppercase letters, and another
smaller square of n rows and columns of uppercase letters, we want to
count the number of appearances in the big square of the small square
in all the rotated forms.

Input
-----
The input will consist of a series of problems, with each problem in
a series of lines. In the first line, the dimension of the two squares,
N and n (with 0 < n <= N), is indicated by two integer numbers
separated by a space. The N lines of the first square appear in the
following N lines of the input, and then then lines of the second
square appear in the following n lines. The characters in a line
are one after another, without spaces. The end of the sequence of
problems is indicated with a case where N = 0 and n = 0.

Output
------
The solutions of the different problems appear in successive lines.
For each problem the output consists of a line with four integers,
which are the number of times each rotation of the small square
appears in the big square. The first number corresponds to the number
of appearances of the small square without rotations, the second
to the appearances of the square rotated 90 degrees (clockwise),
the third to the square rotated 180 degrees, and the fourth to
the square rotated 270 degrees.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <array>
#include <cassert>
#include <cstddef>
#include <utility>

template<typename T>
bool is_submatrix(const Matrix<T>& matrix, const Matrix<T>& submatrix,
	std::size_t start_row, std::size_t start_col)
{
	for (std::size_t col = 0; col < submatrix.cols(); ++col)
		for (std::size_t row = 0; row < submatrix.rows(); ++row)
			if (matrix(start_row + row, start_col + col) != submatrix(row, col))
				return false;
	return true;
}

template<typename T>
std::size_t count_submatrices(const Matrix<T>& matrix, const Matrix<T>& submatrix)
{
	const auto max_d_rows = matrix.rows() - submatrix.rows();
	const auto max_d_cols = matrix.cols() - submatrix.cols();

	std::size_t n = 0;
	for (std::size_t col = 0; col <= max_d_cols; ++col)
		for (std::size_t row = 0; row <= max_d_rows; ++row)
			n += is_submatrix(matrix, submatrix, row, col);

	return n;
}

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

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::size_t large_size, small_size;
		if (!read(large_size, small_size) || large_size == 0)
			return false;

		assert(0 < small_size && small_size <= large_size);

		large_sq_.resize(large_size, large_size);
		small_sq_.resize(small_size, small_size);
		return read_matrix(large_sq_) && read_matrix(small_sq_);
	}

	virtual void solve(unsigned int) override
	{
		std::array<std::size_t, 4> n;
		for (std::size_t i = 0; i < 4; ++i)
		{
			if (i > 0)
				rotate(small_sq_);
			n[i] = count_submatrices(large_sq_, small_sq_);
		}

		write_range(n.begin(), n.end(), ' ');
		write_ln();
	}

private:
	Matrix<char> large_sq_;
	Matrix<char> small_sq_;
};

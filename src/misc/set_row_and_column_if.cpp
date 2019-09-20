/*********************************************************************
Set row and column if
---------------------

Modify the given matrix such that if matrix(i, j) is equal to
the given value, this value is assigned to all matrix elements
in the row i and the column j.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <vector>

template<typename T>
void set_row_and_column_if(Matrix<T>& mat, const typename Matrix<T>::Value& value)
{
	std::vector<unsigned char> set_rows(mat.rows(), 0);
	std::vector<unsigned char> set_cols(mat.cols(), 0);

	for (std::size_t row = 0; row < mat.rows(); ++row)
		for (std::size_t col = 0; col < mat.cols(); ++col)
			if (mat(row, col) == value)
			{
				set_rows[row] = 1;
				break;
			}

	for (std::size_t col = 0; col < mat.cols(); ++col)
		for (std::size_t row = 0; row < mat.rows(); ++row)
			if (mat(row, col) == value)
			{
				set_cols[col] = 1;
				break;
			}

	for (std::size_t col = 0; col < mat.cols(); ++col)
		if (set_cols[col])
			for (std::size_t row = 0; row < mat.rows(); ++row)
				mat(row, col) = value;

	for (std::size_t row = 0; row < mat.rows(); ++row)
		if (set_rows[row])
			for (std::size_t col = 0; col < mat.cols(); ++col)
				mat(row, col) = value;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t rows, cols;

		read(rows, cols);
		mat_.resize(rows, cols);
		read_matrix(mat_);
	}

	virtual void solve(unsigned int) override
	{
		set_row_and_column_if(mat_, 1);
		write_matrix(mat_);
	}

private:
	Matrix<unsigned int> mat_;
};

MAIN

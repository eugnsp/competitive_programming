/*********************************************************************
Integral determinant
--------------------
UVa ID: 006 84

Write a program to find the determinant of an integral square matrix.
Note that the answer shall be aninteger. That is, all the operations
needed are just integer operations; by reducing to floating numbers
would result in the round-off errors, which will be considered as the
wrong answer. Do not worry about the problem of integral overflows
problem. You can assume that the given data set will not cause the
integer overflow problem. What is emphasized here is the required
integer precision.

Input
-----
Several sets of integral matrices. The inputs are just a list of
integers. Within each set, the first integer (in a single line)
represents the size of the matrix, n, which can be as large as 30.
After n, there will be n lines representing the n rows of the matrix;
each line (row) contains exactly n integers. Thus, there is totally
n^2 integers for the particular matrix. These matrices will occur
repeatedly in the input as the pattern described above. An integer
n = 0 signifies the end of input.

Output
------
For each matrix of the input, calculate its (integral) determinant and
output them in a line. Output asingle star (*) to signify the end of
outputs.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cassert>

// Returns the determinant of the (matrix) using the Bareiss algorithm
template<typename T>
T bareiss_int_det(Matrix<T>& matrix)
{
	assert(matrix.rows() == matrix.cols());
	const auto n = matrix.rows();

	T sign = 1;
	for (std::size_t k = 0; k < n - 1; ++k)
	{
		// Find a column with a non-zero element
		auto nz_col = k;
		while (nz_col < n && matrix(k, nz_col) == 0)
			++nz_col;

		// If no such column exists, the matrix is singular
		if (nz_col == n)
			return 0;

		// Swap columns, so that (m_kk) != 0
		if (nz_col > k)
		{
			matrix.swap_cols(k, nz_col);
			sign *= -1;
		}

		for (auto j = k + 1; j < n; ++j)
			for (auto i = k + 1; i < n; ++i)
			{
				matrix(i, j) = matrix(k, k) * matrix(i, j) - matrix(i, k) * matrix(k, j);

				if (k > 0)
				{
					assert(matrix(k - 1, k - 1) != 0);
					matrix(i, j) /= matrix(k - 1, k - 1);
				}
			}
	}

	return sign * matrix(n - 1, n - 1);
}

class CP : public CP2
{
private:
	using T = long long;

private:
	virtual bool read_input() override
	{
		std::size_t n;
		if (!read(n) || n == 0)
			return false;

		m_.resize(n, n);
		return read_matrix(m_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(bareiss_int_det(m_));
	}

	virtual void end() override
	{
		write_ln('*');
	}

private:
	Matrix<T> m_;
};

MAIN


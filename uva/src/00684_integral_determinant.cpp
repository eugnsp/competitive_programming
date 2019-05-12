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
#include <utility>

using Size = unsigned int;
using Element = int;
using M = Matrix<Element, Size>;

// Returns the determinant of the (matrix)
Element int_det(M& matrix)
{
	// The fraction-free elimination algorithm
	//
	// This algorithm is a variant of the Gauss-Jordan elimination method.
	// Two columns are successively subtracted from one another according to
	// the Euclid GCD algorithm until the top element col2[0] becomes zero:
	// 	1) col1 -= r * col2, where r = col1[0] / col2[0],
	// 	2) col1 <-> col2,
	// Finally, columns are swapped if necessary (if the total number of
	// (col1) and (col2) indices swaps is odd).

	assert(matrix.rows() == matrix.cols());
	const auto n = matrix.rows();

	Element det = 1;
	for (Size i = 0; i < n; ++i)
	{
		for (auto j = i + 1; j < n; ++j)
		{
			auto col1 = i;
			auto col2 = j;
			while (matrix(i, col2) != 0)
			{
				auto r = matrix(i, col1) / matrix(i, col2);
				if (r != 0)
					for (auto k = i; k < n; ++k)
						matrix(k, col1) -= r * matrix(k, col2);
				std::swap(col1, col2);
			}

			if (col2 != j)
			{
				det *= -1;
				for (auto k = i; k < n; ++k)
					std::swap(matrix(k, j), matrix(k, col2));
			}
		}

		det *= matrix(i, i);
		if (det == 0)
			return 0;
	}

	return det;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		Size n;
		if (!read(n) || n == 0)
			return false;

		m_.resize(n, n);
		return read_matrix(m_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(int_det(m_));
	}

	virtual void end() override
	{
		write_ln('*');
	}

private:
	M m_;
};

MAIN


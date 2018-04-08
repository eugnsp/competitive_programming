/*********************************************************************
Integral determinant
--------------------
UVa ID: 006 84

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include "util.hpp"
#include <cassert>

using Size = unsigned int;
using Element = int;
using M = Matrix<Element, Size>;

// The Bareiss algorithm

// Returns the determinant of the (matrix)
Element bareiss_int_det(M& matrix)
{
	assert(matrix.rows() == matrix.cols());
	const auto n = matrix.rows();

	Element sign = 1;
	for (Size k = 0; k < n - 1; ++k)
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

				assert(matrix(k - 1, k - 1) != 0);
				if (k > 0)
					matrix(i, j) /= matrix(k - 1, k - 1);
			}
	}

	return sign * matrix(n - 1, n - 1);
}

class CP : public CP2
{
private:
	using T = long long;

private:
	virtual bool read_input(std::istream& in) override
	{
		Size n;
		in >> n;
		if (n == 0)
			return false;

		assert(between(n, 1, 30));

		m_.resize(n, n);
		in >> m_;

		return true;
	}

	virtual void solve(std::ostream& out, unsigned int) const override
	{
		out << bareiss_int_det(m_) << '\n';
	}

	virtual void end(std::ostream& out) override
	{
		out << "*\n";
	}

private:
	mutable M m_;
};

int main()
{
	CP p;
	return p.run();
}

/*********************************************************************
Integral determinant
--------------------
UVa ID: 684

Goal:	find the determinant of a square matrix with integral entries.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <cassert>

class Integral_determinant : public CP2
{
private:
	using T = long long;

private:
	virtual bool read_input(std::istream& in) override
	{
		// <matrix size = n>
		// <a_11> ... <a_1n>
		// ...
		// <a_n1> ... <a_nn>

		std::size_t n;
		in >> n;
		if (n == 0)
			return false;

		assert(1 <= n && n <= 30);

		m_.resize(n, n);
		for (std::size_t i = 0; i < n; ++i)
			for (std::size_t j = 0; j < n; ++j)
				in >> m_(i, j);

		return true;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		out << bareiss_det(m_) << '\n';
	}

	static T bareiss_det(Matrix<T>& m)
	{
		assert(m.rows() == m.cols());
		const auto n = m.rows();

		/*********************************************************************
		The Bareiss algorithm
		
		Google for the description.
		**********************************************************************/

		T sign = 1;
		for (std::size_t k = 0; k < n - 1; ++k)
		{
			// Find a column with a non-zero element
			auto nz_col = k;
			while (nz_col < n && m(k, nz_col) == 0)
				++nz_col;

			// If no such column exists, the matrix is singular
			if (nz_col == n)
				return 0;

			// Swap columns, so that (m_kk) != 0
			if (nz_col > k)
			{
				m.swap_cols(k, nz_col);
				sign *= -1;
			}

			for (std::size_t j = k + 1; j < n; ++j)
				for (std::size_t i = k + 1; i < n; ++i)
				{
					m(i, j) = m(k, k) * m(i, j) - m(i, k) * m(k, j);

					assert(m(k - 1, k - 1) != 0);
					if (k > 0)
						m(i, j) /= m(k - 1, k - 1);
				}
		}

		return sign * m(n - 1, n - 1);
	}

	virtual void end(std::ostream& out) override
	{
		out << "*\n";
	}

private:
	Matrix<T> m_;
};

int main()
{
	Integral_determinant p;
	return p.run();
}

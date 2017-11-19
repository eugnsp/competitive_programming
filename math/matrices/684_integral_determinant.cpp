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
	using T = int;

private:
	virtual bool read_input(std::istream& in) override
	{
		// <matrix size = n>
		// <a_11> ... <a_1n>
		// ...
		// <a_n1> ... <a_nn>

		in >> n_;
		if (n_ == 0)
			return false;

		assert(1 <= n_ && n_ <= 30);

		m_.resize(n_, n_);
		for (std::size_t i = 0; i < n_; ++i)
			for (std::size_t j = 0; j < n_; ++j)
				in >> m_(i, j);

		return true;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		/*********************************************************************
		The fraction-free triangulation algorithm

		This algorithm is a variant of the Gauss–Jordan elimination method.
		Two columns are successively subtracted from one another according to
		the Euclid GCD algorithm until the top element col2[0] becomes zero:
			1) col1 -= r * col2, where r = col1[0] / col2[0],
			2) col1 <-> col2,
		Finally, columns are swapped if necessary (if the total number of
		(col1) and (col2) indices swaps is odd).
		**********************************************************************/

		T det = 1;
		for (std::size_t i = 0; i < n_; ++i)
		{
			for (std::size_t j = i + 1; j < n_; ++j)
			{
				auto col1 = i;
				auto col2 = j;
				while (m_(i, col2) != 0)
				{
					auto r = m_(i, col1) / m_(i, col2);
					if (r != 0)
						for (std::size_t k = i; k < n_; ++k)
							m_(k, col1) -= r * m_(k, col2);
					std::swap(col1, col2);
				}

				if (col2 != j)
				{
					det *= -1;
					for (std::size_t k = i; k < n_; ++k)
						std::swap(m_(k, j), m_(k, col2));
				}
			}

			det *= m_(i, i);
			if (det == 0)
				break;
		}

		out << det << '\n';
	}

	virtual void end(std::ostream& out) override
	{
		out << "*\n";
	}

private:
	std::size_t n_;
	Matrix<T> m_;
};

int main()
{
	Integral_determinant p;
	return p.run();
}

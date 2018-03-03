/*********************************************************************
Integral determinant
--------------------
UVa ID: 684

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include "util.hpp"
#include <cassert>
#include <utility>

using Size = unsigned int;
using Element = int;

/*********************************************************************
The fraction-free elimination algorithm

This algorithm is a variant of the Gauss–Jordan elimination method.
Two columns are successively subtracted from one another according to
the Euclid GCD algorithm until the top element col2[0] becomes zero:
	1) col1 -= r * col2, where r = col1[0] / col2[0],
	2) col1 <-> col2,
Finally, columns are swapped if necessary (if the total number of
(col1) and (col2) indices swaps is odd).
**********************************************************************/

Element int_det(Matrix<Element, Size>& matrix)
{
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
			break;
	}

	return det;
}

class CP : public CP2
{
private:
	virtual bool read_input(std::istream& in) override
	{
		Size n;
		in >> n;
		if (n == 0)
			return false;

		assert(between(n, 1, 30));

		m_.resize(n, n);
		read_matrix(in, m_);

		return true;
	}

	virtual void solve(std::ostream& out, std::size_t) const override
	{
		out << int_det(m_) << '\n';
	}

	virtual void end(std::ostream& out) override
	{
		out << "*\n";
	}

private:
	mutable Matrix<Element, Size> m_;
};

int main()
{
	CP p;
	return p.run();
}

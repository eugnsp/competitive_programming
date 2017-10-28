/*********************************************************************
Maximum sum
-----------
UVa ID: 108

Goal:	for a given matrix find the sub-matrix with the largest
		sum of its elements.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include "dp_kadane_max_sum.hpp"
#include <cstddef>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

class Maximum_sum : public CP2
{
private:
	virtual bool read_input() override
	{
		// <n>
		// <m_11> ... <m_1n>
		// ...
		// <m_n1> ... <m_nn>

		std::size_t n;
		if (!(std::cin >> n))
			return false;

		assert(0 < n && n <= 100);

		matrix.resize(n, n);
		for (std::size_t i = 0; i < n; ++i)
			for (std::size_t j = 0; j < n; ++j)
				std::cin >> matrix(i, j);

		return true;
	}

	virtual void solve(std::size_t) override
	{
		auto max_sum = matrix(0, 0);
		std::vector<decltype(max_sum)> partial_row_sum(matrix.rows());

		for (std::size_t start_col = 0; start_col < matrix.cols(); ++start_col)
		{
			std::fill(partial_row_sum.begin(), partial_row_sum.end(), 0);
			for (std::size_t end_col = start_col; end_col < matrix.cols(); ++end_col)
			{
				for (std::size_t j = 0; j < matrix.rows(); ++j)
					partial_row_sum[j] += matrix(j, end_col);

				const auto sum = kadane_max_sum(partial_row_sum.cbegin(), partial_row_sum.cend());
				max_sum = std::max(max_sum, sum);
			}
		}

		std::cout << max_sum << '\n';
	}

private:
	Matrix<int> matrix;
};

int main()
{
	Maximum_sum p;
	return p.run();
}
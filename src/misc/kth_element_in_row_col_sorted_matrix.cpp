/*********************************************************************
K-th element in a row-column sorted matrix
------------------------------------------

Find the k-th smallest element in the given NxN matrix, in which
every row and column is sorted in the non-decreasing order.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <queue>
#include <utility>
#include <vector>

template<class T>
using Min_heap = std::priority_queue<T, std::vector<T>, std::greater<T>>;

template<typename T>
T kth_element(const Matrix<T>& matrix, std::size_t k)
{
	assert(k < matrix.rows() * matrix.cols());

	Min_heap<std::pair<T, Position>> min_heap;

	for (std::size_t row = 0; row < std::min(k + 1, matrix.rows()); ++row)
	{
		const Position p{row, 0};
		min_heap.push({matrix(p), p});
	}

	while (true)
	{
		const auto top = min_heap.top();
		if (k-- == 0)
			return top.first;

		min_heap.pop();

		if (const auto pos = top.second + Position{0, 1}; pos.col < matrix.cols())
			min_heap.push({matrix(pos), pos});
	}
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t size;
		read(size);

		matrix_.resize(size, size);
		read_matrix(matrix_);

		read(k_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(kth_element(matrix_, k_ - 1));		// to zero-based indexing
	}

private:
	Matrix<int> matrix_;
	std::size_t k_;
};

MAIN

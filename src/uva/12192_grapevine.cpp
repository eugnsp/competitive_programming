/*********************************************************************
Grapevine
---------
UVa ID: 121 92

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

// Note: binary search along diagonals is not faster for judge data

#include "base.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

template<typename T>
std::size_t find_last_row_of_square(
	const Matrix<T>& m, std::size_t row, std::size_t col, const typename Matrix<T>::Value& value)
{
	while (row < m.rows() && col < m.cols() && m(row, col) <= value)
		++row, ++col;
	return row;
}

template<typename T>
std::size_t max_size(const Matrix<T>& m, const typename Matrix<T>::Value& min, const typename Matrix<T>::Value& max)
{
	assert(min <= max);
	std::size_t max_size = 0;

	std::size_t row = m.rows() - 1;
	for (std::size_t col = 0; col + max_size < m.cols(); ++col)
	{
		const auto first = m.begin_col(col);
		const auto last = first + row + 1;
		const auto begin = std::lower_bound(first, last, min);
		if (begin == last)
			continue;

		row = static_cast<std::size_t>(begin - first);
		const auto last_row = row + max_size;
		const auto last_col = col + max_size;
		if (last_row < m.rows() && last_col < m.cols())
			max_size += find_last_row_of_square(m, last_row, last_col, max) - last_row;
	}

	return max_size;
}

using Height = unsigned int;

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::size_t n_rows, n_cols;
		read(n_rows, n_cols);

		if (n_rows == 0 && n_cols == 0)
			return false;

		assert(n_rows <= 500 && n_cols <= 500);
		land_.resize(n_rows, n_cols);
		read_matrix(land_);

		return read_size_vec(queries_);
	}

	virtual void solve(unsigned int) override
	{
		for (auto& q : queries_)
			write_ln(max_size(land_, q.first, q.second));
		write_ln('-');
	}

private:
	Matrix<Height> land_;
	std::vector<std::pair<Height, Height>> queries_;
};

MAIN

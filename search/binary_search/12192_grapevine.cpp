/*********************************************************************
Grapevine
---------
UVa ID: 121 92

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

// Note: binary search along diagonals is not faster for judge data

#include "base.hpp"
#include "io.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cassert>
#include <vector>
#include <utility>

using Height = unsigned int;
using Size = unsigned int;
using M = Matrix<Height, Size>;

Size find_end_row_of_square(const M& m, Size row, Size col, Height value)
{
	while (row < m.rows() && col < m.cols() && m(row, col) <= value)
		++row, ++col;
	return row;
}

Size max_size(const M& m, Height min, Height max)
{
	assert(min <= max);
	Size max_size = 0;

	Size row = m.rows() - 1;
	for (Size col = 0; col + max_size < m.cols(); ++col)
	{
		const auto first = m.begin_col(col);
		const auto last = first + row + 1;
		const auto begin = std::lower_bound(first, last, min);
		if (begin == last)
			continue;

		row = static_cast<Size>(begin - first);
		const auto end_row = row + max_size;
		const auto end_col = col + max_size;
		if (end_row < m.rows() && end_col < m.cols())
			max_size += find_end_row_of_square(m, end_row, end_col, max) - end_row;
	}

	return max_size;
}

class CP : public CP2
{
private:
	virtual bool read_input(std::istream& in) override
	{
		Size n_rows, n_cols;
		in >> n_rows >> n_cols;

		if (n_rows == 0 && n_cols == 0)
			return false;

		assert(n_rows <= 500 && n_cols <= 500);
		land_.resize(n_rows, n_cols);
		in >> land_;

		std::size_t n_queries;
		in >> n_queries;
		assert(n_queries <= 10000);

		read_vector(in, n_queries, queries_);
		return true;
	}

	virtual void solve(std::ostream& out, unsigned int) const override
	{
		for (auto& q : queries_)
			out << max_size(land_, q.first, q.second) << '\n';
		out << '-' << '\n';
	}

private:
	M land_;
	std::vector<std::pair<Height, Height>> queries_;
};

int main()
{
	CP p;
	return p.run();
}

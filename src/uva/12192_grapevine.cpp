/*********************************************************************
Grapevine
---------
UVa ID: 121 92

In Quadradonia, all rural properties are square, all have the same
area, all are perfectly flat and all have the sides aligned to the
North-South and West-East axes. Since properties are flat, the
hills in Quadradonia look like a series of huge stairs' steps, with
different heights. In a certain mountain, an interesting situation
occurs in a rectangular area of NxM properties. Starting from anywhere
within the region, traversing it in the West to East direction, the
properties have non-descending heights. Similarly, traversing that
region in the North to South direction, starting from anywhere, the
properties have also non-descending heights. A large wine company in
Quadradonia wants to rent some properties from that region to grow
winegrapes. The company is interested in some special varieties of
wine grapes, which are productive only if grown in properties whose
heights are within a certain interval. That is, the company is
interested in renting properties whose heights are equal to or higher
than a given altitude L, and equal to or lower than a given altitude U.
To make it easier for harvesting, the rented properties must form a
contiguous area. And since everyone in Quadradonia likes squares, the
area to be rented must have the shape of a square. The company has not
yet decided which variety of grapes it will grow, and therefore it has
a list of queries involving intervals, one for each grape variety. The
figure below shows an area of interest of dimensions 4x5 (in number of
properties) with examples of areas the company could rent to grow
grapes in heights within the intervals given in the picture.
You must write a program that, given the description of the rectangular
area of interest in the mountain, and a list of queries containing
height intervals, determines, for each query, the largest side, in
number of properties, of a contiguous square area with heights within
the specified interval.

Input
-----
The input contains several test cases. The first line of a test
case contains two integers N and M, separated by a single space,
representing respectively the number of properties in the North-South
direction (1 <= N <= 500) and the number of properties in the West-East
direction (1 <= M <= 500) of the region of interest. Each of the next
N lines contains M integers H(i, j), separated by single spaces,
indicating the heights of the properties in the region of interest.
The next line contains an integer Q indicatingthe number of queries
(1 <= Q <= 10^4). Each of the next Q lines describes a query, and
contains two integers L and U, separated by a single space, indicating
one interval of heights (0 <= L <= U <= 10^5).The heights of properties
to be rented must be greater than or equal toLand less than or equal
to U. The last test case is followed by a line containing two zeros
separated by a single space.

Output
------
For each test case in the input your program must print Q + 1 lines.
Each of the first Q lines must contain a single integer, indicating
the largest side, in number of properties, of a contiguous square area
with heights within the interval specified in the respective input
query. The last line to be printed foreach test case is used as a
separator and must contain a single character '-'.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include "position.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

template<typename T>
std::size_t max_size_from_pos(const Matrix<T>& m, Position pos,
                              const typename Matrix<T>::Value value)
{
	// Binary search along diagonals is not faster for judge data

	std::size_t size = 0;
	while (is_inside_extents(m, pos) && m(pos) <= value)
		++pos.row, ++pos.col, ++size;
	return size;
}

template<typename T>
std::size_t max_size(const Matrix<T>& m,
                     const typename Matrix<T>::Value min,
                     const typename Matrix<T>::Value max)
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
		if (const Position pos{row + max_size, col + max_size}; is_inside_extents(m, pos))
			max_size += max_size_from_pos(m, pos, max);
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

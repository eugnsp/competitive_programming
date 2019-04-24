/*********************************************************************
Discovering paths
-----------------
UVa ID: 130 50

Given a grid with R rows and C columns, you are currently at (0, 0)
and you want to go to the position (R - 1, C - 1). You have only two
kind of movements allowed. From any position (i, j) you can go to
either (i + 1, j) or (i, j + 1). You need to find the number of ways
you can go to (R - 1, C - 1) from (0, 0). Easy, right? But here's
is a slight problem. All the cells are not available all the time.
So while counting the number of ways you need to consider that you
can never step into a cell which is not available right now.

Input
-----
First line will contain an integer T (1 <= T <= 10), which is the
number of test cases. Each case starts with a line R,C and Q. Here,
1 <= R, C <= 1'000 and 1 <= Q <= 10'000. Then, Q queries follow,
each  with four integers a, b, c, d. This means the cells inside the
rectangle with lower left corner at (a, b) and upper right corner at
(c, d) are not available. All the coordinates are given in row major
order with 0-based indexing. The lowermost and leftmost point is
considered to be (0, 0).

Output
------
For each case print a line "Case T", where T is the case number.
For each query in a case, print 3 spaces and then "Query X: W",
where X is query number and W is the number of ways possible for
that particular query. Answer needs to be in modulo 912.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include "position.hpp"
#include <algorithm>
#include <cstddef>
#include <vector>

constexpr unsigned int mod = 912;

using Pos = Position<std::size_t>;

struct Rect
{
	Pos bottom_left;
	Pos top_right;
};

bool read(Rect& rect)
{
	return read(rect.bottom_left, rect.top_right);
}

bool is_in_rect(const Pos& pos, const Rect& rect)
{
	return (rect.bottom_left.row <= pos.row) && (pos.row <= rect.top_right.row) &&
		   (rect.bottom_left.col <= pos.col) && (pos.col <= rect.top_right.col);
}

std::vector<unsigned int> count_paths(
	std::size_t rows, std::size_t cols, const std::vector<Rect>& rects)
{
	Matrix<unsigned int> n_paths(rows, cols);

	for (std::size_t row = 0; row < rows; ++row)
		n_paths(row, 0) = 1;
	for (std::size_t col = 1; col < cols; ++col)
	{
		n_paths(0, col) = 1;
		for (std::size_t row = 1; row < rows; ++row)
			n_paths(row, col) = (n_paths(row - 1, col) + n_paths(row, col - 1)) % mod;
	}

	std::vector<unsigned int> count;
	count.reserve(rects.size());

	for (auto& rect : rects)
	{
		unsigned int cnt = 0;

		// Count paths passing through Ds:
		// .......D..
		// ......D...
		// ...XXX....
		// ...XXX....
		// ..D.......
		// .D........
		// D.........

		const Pos top_right(rows - 1, cols - 1);
		for (auto i = std::min(rect.bottom_left.row, top_right.col - rect.top_right.col); i > 0; --i)
		{
			const Pos pos(rect.bottom_left.row - i, rect.top_right.col + i);
			cnt += n_paths(pos) * n_paths(top_right - pos);
			cnt %= mod;
		}

		for (auto i = std::min(rect.bottom_left.col, top_right.row - rect.top_right.row); i > 0; --i)
		{
			const Pos pos(rect.top_right.row + i, rect.bottom_left.col - i);
			cnt += n_paths(pos) * n_paths(top_right - pos);
			cnt %= mod;
		}

		count.push_back(cnt);
	}

	return count;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(width_, height_);
		read_size_vec(rects_);
	}

	virtual void solve(unsigned int i_case) override
	{
		write_ln("Case ", i_case);
		const auto cnts = count_paths(width_, height_, rects_);
		for (std::size_t i = 0; i < cnts.size(); ++i)
			write_ln("   Query ", i + 1, ": ", cnts[i]);
	}

private:
	std::size_t width_;
	std::size_t height_;
	std::vector<Rect> rects_;
};

/*********************************************************************
Discovering paths
-----------------
UVa ID: 130 50

Given a grid with R rows and C columns, you are currently at (0, 0)
and you want to go to the position (R - 1, C - 1). You have only
two kind of movements allowed. From any position (i, j) you can go to
either (i + 1, j) or (i, j + 1). You need to find the number of ways
you can go to (R - 1, C - 1) from (0, 0). Easy, right? But here
is a slight problem. All the cells are not available all the time.
So while counting the number of ways you need to consider that you
can never step into a cell which is not available right now.

Input
-----
First line will contain an integer T (1 <= T <= 10), which is the
number of test cases. Each case starts with a line R, C and Q. Here,
1 <= R, C <= 1'000 and 1 <= Q <= 10'000. Then, Q queries follow,
each  with four integers a, b, c, d. This means the cells inside
the rectangle with lower left corner at (a, b) and upper right
corner at (c, d) are not available. The lower-most and left-most
point is considered to be (0, 0).

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

struct Rect
{
	std::size_t bottom;
	std::size_t left;
	std::size_t top;
	std::size_t right;
};

bool read(Rect& rect)
{
	return read(rect.bottom, rect.left, rect.top, rect.right);
}

template<typename T>
class Paths_counter
{
public:
	Paths_counter(std::size_t rows, std::size_t cols)
	{
		n_paths_.resize(rows, cols);
		for (std::size_t row = 0; row < rows; ++row)
			n_paths_(row, 0) = 1;
		for (std::size_t col = 1; col < cols; ++col)
		{
			n_paths_(0, col) = 1;
			for (std::size_t row = 1; row < rows; ++row)
				n_paths_(row, col) = (n_paths_(row - 1, col) + n_paths_(row, col - 1)) % mod;
		}
	}

	T operator()(const Rect& rect) const
	{
		// Count paths passing through Ds:
		// .......D..
		// ......D...
		// ...XXX....
		// ...XXX....
		// ..D.......
		// .D........
		// D.........

		const Position top_right(n_paths_.rows() - 1, n_paths_.cols() - 1);

		T cnt = 0;
		for (auto i = std::min(rect.bottom, top_right.col - rect.right); i > 0; --i)
		{
			const Position pos(rect.bottom - i, rect.right + i);
			cnt += n_paths_(pos) * n_paths_(top_right - pos);
			cnt %= mod;
		}
		for (auto i = std::min(rect.left, top_right.row - rect.top); i > 0; --i)
		{
			const Position pos(rect.top + i, rect.left - i);
			cnt += n_paths_(pos) * n_paths_(top_right - pos);
			cnt %= mod;
		}

		return cnt;
	}

private:
	Matrix<T> n_paths_;
};

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(n_rows_, n_cols);
		read_size_vec(rects_);
	}

	virtual void solve(unsigned int i_case) override
	{
		write_ln("Case ", i_case);
		const Paths_counter<unsigned int> counter(n_rows_, n_cols);

		std::size_t i = 1;
		for (auto& rect : rects_)
			write_ln("   Query ", i++, ": ", counter(rect));
	}

private:
	std::size_t n_rows_;
	std::size_t n_cols;
	std::vector<Rect> rects_;
};

MAIN

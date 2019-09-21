/*********************************************************************
Numerical maze
--------------
UVa ID: 008 68

The following figure illustrates a kind of maze:
1 6 5 2
1 2 6 3
2 1 2 2
3 4 3 4
2 1 5 1
Are you able to find a path that takes you from the start to exit
of the maze? You are only allowed to move horizontally or vertically,
diagonal movements are not permitted. The path consists of
subsequences obeying to the following rule: 1; 1,2; 1,2,3; 1,2,3,4;
and so on. Subsequences mayinclude changes of direction. The problem
you have to solve is to determine an entry point and a path that
takes you to the exit point, for a given maze. The start point is
always a cell in the top row of the maze (with the value 1!) and
the exit point is always a cell in the last line of the maze.

Input
-----
The input begins with a single positive integer on a line by itself
indicating the number of the cases following, each of them as
described below. This line is followed by a blank line, and there is
also a blank line between two consecutive inputs. The first input
line contains two positive integers N and M for the number of rows
and columns of the maze, respectively. Each of the N subsequent
lines contains the M cell values, separated by single spaces. Cell
values are greater or equal to 1.

Output
------
For each test case, the output must follow the description below.
The outputs of consecutive cases will be separated by a blank line.
Two lines, the first with the coordinates, row and column, of the
starting cell, and the second with the coordinates of the exit cell.
If there are several solutions, print the one with lexicographically
smallest starting point. If still a tie, print the one with
lexicographically smallest ending point.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <optional>
#include <utility>

template<typename T>
class Numerical_maze
{
public:
	Numerical_maze(const Matrix<T>& maze) : maze_(maze)
	{}

	std::optional<std::pair<std::size_t, std::size_t>> find_path() const
	{
		std::vector<std::size_t> end_cols;
		Matrix<bool> visited(maze_.rows(), maze_.cols(), false);

		for (std::size_t i = 0; i < maze_.cols(); ++i)
			if (maze_(0, i) == 1)
			{
				find_next(end_cols, {1, 1}, {0, i}, visited);
				if (!end_cols.empty())
					return std::make_pair(i, *std::min_element(end_cols.begin(), end_cols.end()));
			}

		return {};
	}

private:
	struct Seq
	{
		std::size_t i;
		std::size_t len;
	};

	void find_next(std::vector<std::size_t>& end_cols, const Seq seq, const Position cell, Matrix<bool>& visited) const
	{
		if (visited(cell))
			return;

		if (cell.row == maze_.rows() - 1)
		{
			end_cols.push_back(cell.col);
			return;
		}

		visited(cell) = true;

		const auto next_seq = (seq.i < seq.len) ? Seq{seq.i + 1, seq.len} : Seq{1, seq.len + 1};

		constexpr Position directions[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
		for (const auto d : directions)
			if (const auto next_cell = cell + d; is_inside_extents(maze_, next_cell) && maze_(next_cell) == next_seq.i)
				find_next(end_cols, next_seq, next_cell, visited);

		visited(cell) = false;
	}

private:
	const Matrix<T>& maze_;
};

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t n_rows, n_cols;
		read(n_rows, n_cols);

		maze_.resize(n_rows, n_cols);
		read_matrix(maze_);
	}

	virtual void solve(unsigned int i_case) override
	{
		const auto path = Numerical_maze{maze_}.find_path();
		assert(path);

		if (i_case > 1)
			write_ln();
		write_ln(1, ' ', path->first + 1);				// to one-based indexing
		write_ln(maze_.rows(), ' ', path->second + 1);	// to one-based indexing
	}

private:
	Matrix<unsigned int> maze_;
};

MAIN

/*********************************************************************
Numerical maze
--------------
UVa ID: 008 68

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cassert>
#include <utility>

using T = unsigned int;
using Pos = Position<T>;
using Maze = Matrix<T, T>;

struct Seq
{
	T i;
	T len;
};

class Numerical_maze
{
public:
	Numerical_maze(const Maze& maze) : maze_(maze)
	{ }

	std::pair<T, T> find_path() const
	{
		std::vector<T> end_cols;
		Matrix<bool, T> visited(maze_.rows(), maze_.cols(), false);

		for (T i = 0; i < maze_.cols(); ++i)
			if (maze_(0, i) == 1)
			{
				find_next(end_cols, {1, 1}, {0, i}, visited);
				if (!end_cols.empty())
					return {i, *std::min_element(end_cols.begin(), end_cols.end())};
			}

		const auto bad_index = static_cast<T>(-1);
		return {bad_index, bad_index};
	}

private:
	void find_next(std::vector<T>& end_cols, Seq seq, Pos cell, Matrix<bool, T>& visited) const
	{
		constexpr Pos directions[] =
			{{1, 0}, {0, 1}, {static_cast<T>(-1), 0}, {0, static_cast<T>(-1)}};

		if (visited(cell))
			return;

		if (cell.row == maze_.rows() - 1)
		{
			end_cols.push_back(cell.col);
			return;
		}

		visited(cell) = true;

		const auto next_seq = (seq.i < seq.len) ? Seq{seq.i + 1, seq.len} : Seq{1, seq.len + 1};
		for (const auto d : directions)
		{
			const auto next_cell = cell + d;
			if (is_inside(next_cell) && maze_(next_cell) == next_seq.i)
				find_next(end_cols, next_seq, next_cell, visited);
		}

		visited(cell) = false;
	}

	bool is_inside(Pos cell) const
	{
		return cell.row < maze_.rows() && cell.col < maze_.cols();
	}

private:
	const Maze& maze_;
};

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		T n_rows, n_cols;
		read(n_rows, n_cols);

		maze_.resize(n_rows, n_cols);
		read(maze_);
	}

	virtual void solve(unsigned int i_case) override
	{
		const Numerical_maze maze(maze_);
		const auto path = maze.find_path();

		if (i_case > 0)
			write_ln();
		write_ln(1, ' ', path.first + 1);
		write_ln(maze_.rows(), ' ', path.second + 1);
	}

private:
	Maze maze_;
};

MAIN(CP)

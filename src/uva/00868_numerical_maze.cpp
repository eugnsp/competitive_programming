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
#include <cstddef>
#include <utility>

using Maze = Matrix<std::size_t>;

struct Seq
{
	std::size_t i;
	std::size_t len;
};

class Numerical_maze
{
public:
	Numerical_maze(const Maze& maze) : maze_(maze)
	{}

	std::pair<std::size_t, std::size_t> find_path() const
	{
		std::vector<std::size_t> end_cols;
		Matrix<bool> visited(maze_.rows(), maze_.cols(), false);

		for (std::size_t i = 0; i < maze_.cols(); ++i)
			if (maze_(0, i) == 1)
			{
				find_next(end_cols, {1, 1}, {0, i}, visited);
				if (!end_cols.empty())
					return {i, *std::min_element(end_cols.begin(), end_cols.end())};
			}

		const auto bad_index = static_cast<std::size_t>(-1);
		return {bad_index, bad_index};
	}

private:
	void find_next(std::vector<std::size_t>& end_cols, Seq seq, const Position cell, Matrix<bool>& visited) const
	{
		constexpr Position directions[] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

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

	bool is_inside(const Position cell) const
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
		std::size_t n_rows, n_cols;
		read(n_rows, n_cols);

		maze_.resize(n_rows, n_cols);
		read_matrix(maze_);
	}

	virtual void solve(unsigned int i_case) override
	{
		const Numerical_maze maze(maze_);
		const auto path = maze.find_path();

		if (i_case > 1)
			write_ln();
		write_ln(1, ' ', path.first + 1);
		write_ln(maze_.rows(), ' ', path.second + 1);
	}

private:
	Maze maze_;
};

MAIN

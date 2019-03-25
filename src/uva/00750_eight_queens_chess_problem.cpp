/*********************************************************************
8 queens chess problem
----------------------
UVa ID: 007 50

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "position.hpp"
#include <array>
#include <cassert>
#include <iomanip>
#include <vector>

using Coord = unsigned int;
using Pos = Position<Coord>;

class Eight_queens
{
private:
	static constexpr Coord board_size = 8;
	using Board = std::array<Coord, board_size>;
	using Boards = std::vector<Board>;

public:
	Eight_queens(Pos fixed_queen) : fixed_queen_(fixed_queen)
	{
		assert(fixed_queen_.row < board_size && fixed_queen_.col < board_size);
	}

	Boards enumerate_boards() const
	{
		Boards boards;
		Board init_board;

		place_queen(init_board, fixed_queen_);
		get_next(boards, init_board, get_next_col(static_cast<Coord>(-1)));
		return boards;
	}

private:
	void get_next(Boards& boards, Board& board, Coord col) const
	{
		for (Coord row = 0; row < board_size; ++row)
		{
			const Pos pos_to_try{row, col};
			if (can_be_placed(board, pos_to_try))
			{
				place_queen(board, pos_to_try);
				const auto next_col = get_next_col(col);
				if (next_col < board_size)
					get_next(boards, board, next_col);
				else
					boards.push_back(board);
			}
		}
	}

	static void place_queen(Board& board, Pos queen)
	{
		board[queen.col] = queen.row;
	}

	unsigned int get_next_col(Coord col) const
	{
		++col;
		if (col == fixed_queen_.col)
			++col;

		return col;
	}

	bool can_be_placed(const Board& board, Pos queen) const
	{
		if (can_capture(queen, fixed_queen_))
			return false;

		// Check columns before the given one, columns
		// after it contain either the fixed queen
		// or no queens (by definition)
		for (Coord c = 0; c < queen.col; ++c)
			if (can_capture(queen, {board[c], c}))
				return false;

		return true;
	}

	static bool can_capture(Pos queen1, Pos queen2)
	{
		// Same row or same column
		if (queen1.row == queen2.row || queen1.col == queen2.col)
			return true;

		// Same diagonal
		return abs_diff(queen1.row, queen2.row) == abs_diff(queen1.col, queen2.col);
	}

	template<typename T>
	static T abs_diff(T x, T y)
	{
		return y > x ? y - x : x - y;
	}

private:
	const Pos fixed_queen_;
};

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(first_queen_.row, first_queen_.col);
		--first_queen_.row; // To zero-based indexing
		--first_queen_.col;
	}

	virtual void solve(unsigned int i_case) override
	{
		const Eight_queens queens(first_queen_);

		if (i_case > 1)
			write_ln();
		write_ln("SOLN       COLUMN");
		write_ln(" #      1 2 3 4 5 6 7 8");
		write_ln();

		unsigned int sol_index = 1;
		for (auto& board : queens.enumerate_boards())
		{
			write_ln(std::setw(2), sol_index++, "      ");

			// To one-based indexing
			write_vec(board, [](Coord row) { return row + 1; }, ' ');
			write_ln();
		}
	}

private:
	Pos first_queen_;
};



/*********************************************************************
Eight queens chess problem
--------------------------
UVa ID: 007 50

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "position.hpp"
#include <array>
#include <cassert>
#include <iomanip>
#include <vector>

class Eight_queens
{
private:
	static constexpr std::size_t board_size = 8;

public:
	using Board = std::array<std::size_t, board_size>;

public:
	Eight_queens(const Position fixed_queen) : fixed_queen_(fixed_queen)
	{
		assert(fixed_queen_.row < board_size && fixed_queen_.col < board_size);
	}

	template<class Fn>
	void enumerate_boards(Fn&& fn) const
	{
		Board init_board;

		place_queen(init_board, fixed_queen_);
		get_next(fn, init_board, get_next_col(-1));
	}

private:
	template<class Fn>
	void get_next(Fn&& fn, Board& board, const std::size_t col) const
	{
		for (std::size_t row = 0; row < board_size; ++row)
		{
			const Position pos_to_try{row, col};
			if (can_be_placed(board, pos_to_try))
			{
				place_queen(board, pos_to_try);
				const auto next_col = get_next_col(col);
				if (next_col < board_size)
					get_next(fn, board, next_col);
				else
					fn(board);
			}
		}
	}

	static void place_queen(Board& board, const Position queen)
	{
		board[queen.col] = queen.row;
	}

	std::size_t get_next_col(std::size_t col) const
	{
		++col;
		return col + (col == fixed_queen_.col);
	}

	bool can_be_placed(const Board& board, const Position queen) const
	{
		if (can_capture(queen, fixed_queen_))
			return false;

		// Check columns before the given one, columns
		// after it contain either the fixed queen
		// or no queens (by definition)
		for (std::size_t c = 0; c < queen.col; ++c)
			if (can_capture(queen, {board[c], c}))
				return false;

		return true;
	}

	static bool can_capture(const Position queen1, const Position queen2)
	{
		// Same row or same column
		if (queen1.row == queen2.row || queen1.col == queen2.col)
			return true;

		// Same diagonal
		return abs_diff(queen1.row, queen2.row) == abs_diff(queen1.col, queen2.col);
	}

	template<typename T>
	static T abs_diff(const T x, const T y)
	{
		return y > x ? y - x : x - y;
	}

private:
	const Position fixed_queen_;
};

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(first_queen_.row, first_queen_.col);
		first_queen_.to_zero_based();
	}

	virtual void solve(unsigned int i_case) override
	{
		if (i_case > 1)
			write_ln();
		write_ln("SOLN       COLUMN");
		write_ln(" #      1 2 3 4 5 6 7 8");
		write_ln();

		const Eight_queens queens(first_queen_);

		unsigned int sol_index = 1;
		queens.enumerate_boards([&sol_index](const Eight_queens::Board& board)
		{
			write_ln(std::setw(2), sol_index++, "      ");

			// To one-based indexing
			write_vec(board, [](std::size_t row) { return row + 1; }, ' ');
			write_ln();
		});
	}

private:
	Position first_queen_;
};

MAIN

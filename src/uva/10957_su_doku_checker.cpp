/*********************************************************************
Sudoku
------
UVa ID: 109 57

The best logical puzzles often are puzzles that are based on a simple
idea. Su Doku is one such type of puzzle. Although Su Dokus have been
around for some twenty years, in the last few years they conquered the
world exponentially. Hundreds of newspapers and websites are now
publishing them on a daily basis. For those of you unfamiliar with
these puzzles, let me give a brief introduction. To solve the puzzle
you have to fill the empty places with digits according to the
following rules:
	every row should contain the digits 1 to 9 exactly once,
	every column should contain the digits 1 to 9 exactly once,
	every 3x3 sub-grid should contain the digits 1 to 9 exactly once.
A well formed Su Doku can be solved with paper and pencil using logical
deduction only. To be well formed it should be legal (no row, column or
sub-grid contains a digit more than once), solvable (the empty places
can all be filled while respecting the rules) and unique (there is only
one solution). This is what your program is going to check.

Input
-----
The input contains several (partially) filled grids, each representing
a Su Doku puzzle. For every puzzle there are 9 lines with 9 digits
giving the puzzle in row major order. Empty places in the puzzle are
represented by the digit "0". Digits on a line are separated by one
space. The grids are separated by one empty line. The first grid in
the sample input represents the puzzle given in the picture.

Output
------
For every grid in the input, determine one of the following four
verdicts:
	"Illegal" if the puzzle violates one of the three rules,
	"Unique" if only one solution exists,
	"Ambiguous" if more than one solution exists,
	"Impossible" if no solution exists.
Print one line per grid, in the format:
	Case N: VERDICT.
where N is the case number, starting from 1, and VERDICT is one of the
four words in the list. Note: an "Illegal" puzzle is also "Impossible",
of course, but your program should print "Illegal" in that case. Only
print "Impossible" if the input doesn't violate one of the three rules,
but the puzzle still can't be solved.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "static_matrix.hpp"
#include <cassert>
#include <cstdint>

constexpr std::size_t small_size = 3;
constexpr std::size_t size = small_size * small_size;

using Mask = std::uint16_t;
using Pos = Position<std::size_t>;

enum class Status
{
	ILLEGAL,
	UNIQUE,
	AMBIGUOUS,
	IMPOSSIBLE
};

struct Pattern
{
	Matrix<Mask, size, size> cells;
	Matrix<Mask, size, 1> rows;
	Matrix<Mask, size, 1> cols;
	Matrix<Mask, small_size, small_size> rects;
};

constexpr Mask digit_to_mask(const unsigned int digit)
{
	return digit == 0 ? 0 : static_cast<Mask>(1) << (digit - 1);
}

// Prepares initial masks and checks if the initial pattern is legal
bool prepare_masks(Pattern& pattern)
{
	pattern.rows.fill(0);
	pattern.cols.fill(0);
	pattern.rects.fill(0);

	for (std::size_t col = 0; col < size; ++col)
		for (std::size_t row = 0; row < size; ++row)
		{
			const auto m = pattern.cells(row, col);

			if (pattern.rows[row] & m)
				return false;
			pattern.rows[row] |= m;

			if (pattern.cols[col] & m)
				return false;
			pattern.cols[col] |= m;

			if (pattern.rects(row / small_size, col / small_size) & m)
				return false;
			pattern.rects(row / small_size, col / small_size) |= m;
		}

	return true;
}

Pos find_first_empty(const Pattern& pattern, const Pos& last)
{
	for (auto i = pattern.cells.index(last) + 1; i < size * size; ++i)
		if (!pattern.cells[i])
			return pattern.cells.pos(i);

	return {size, size};
}

Mask available_digits(const Pattern& pattern, const Pos& pos)
{
	return ~(
		pattern.rows[pos.row] | pattern.cols[pos.col] |
		pattern.rects(pos.row / small_size, pos.col / small_size));
}

void toggle(Pattern& pattern, const Pos& pos, const Mask mask)
{
	pattern.cells(pos) ^= mask;
	pattern.rows[pos.row] ^= mask;
	pattern.cols[pos.col] ^= mask;
	pattern.rects(pos.row / small_size, pos.col / small_size) ^= mask;
}

// Solves a Sudoku puzzle using backtracking and counts the number of solutions,
// aborts after the second solution has been found
bool solve_sudoku(Pattern& pattern, const Pos last, std::size_t& n_solutions)
{
	const auto next = find_first_empty(pattern, last);
	if (next == Pos{size, size})
	{
		++n_solutions;
		return true;
	}

	const auto available_mask = available_digits(pattern, next);
	for (Mask digit_mask = 1; digit_mask <= digit_to_mask(size); digit_mask <<= 1)
		if (digit_mask & available_mask)
		{
			toggle(pattern, next, digit_mask);
			if (solve_sudoku(pattern, next, n_solutions) && n_solutions > 1)
				return true;

			toggle(pattern, next, digit_mask);
		}

	return false;
}

Status check_sudoku(Pattern& pattern)
{
	if (!prepare_masks(pattern))
		return Status::ILLEGAL;

	std::size_t n_solutions = 0;
	solve_sudoku(pattern, Pos{static_cast<std::size_t>(-1), 0}, n_solutions);

	switch (n_solutions)
	{
	case 0:
		return Status::IMPOSSIBLE;

	case 1:
		return Status::UNIQUE;

	default:
		return Status::AMBIGUOUS;
	}
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_matrix<unsigned int>(board_.cells, digit_to_mask);
	}

	virtual void solve(unsigned int i_case) override
	{
		const auto status = check_sudoku(board_);

		write("Case ", i_case + 1, ": ");
		switch (status)
		{
		case Status::ILLEGAL:
			write_ln("Illegal.");
			break;

		case Status::UNIQUE:
			write_ln("Unique.");
			break;

		case Status::AMBIGUOUS:
			write_ln("Ambiguous.");
			break;

		case Status::IMPOSSIBLE:
			write_ln("Impossible.");
		}
	}

private:
	Pattern board_;
};

MAIN(CP)

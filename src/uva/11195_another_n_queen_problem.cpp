/*********************************************************************
Another n-queen problem
-----------------------
UVa ID: 111 95

I guess the n-queen problem is known by every person who has studied
backtracking. In this problem you should count the number of placement
of n queens on an nXn board so that no two queens attack each other.
To make the problem a little bit harder (easier?), there are some bad
squares where queens cannot be placed. Please keep in mind that bad
squares cannot be used to block queens' attack. Even if two solutions
become the same after some rotations and reflections, they are
regarded as different. So there are exactly 92 solutions to the
traditional 8-queen problem.

Input
-----
The input consists of at most 10 test cases. Each case contains one
integer n (3 <= n <= 15) in the first line. The following n lines
represent the board, where empty squares are represented by dots '.',
bad squares are represented by asterisks '*'. The last case is
followed by a single zero, which should not be processed.

Output
------
For each test case, print the case number and the number of solutions.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "bit.hpp"
#include <cassert>
#include <cstddef>
#include <vector>

using Mask = unsigned int;

class N_queens
{
private:
	using Board = std::vector<std::size_t>;

public:
	N_queens(const std::vector<Mask>& bad_squares) : board_size_(bad_squares.size())
	{
		good_squares_ = bad_squares;

		// Convert bad squares into good ones
		for (Mask& mask : good_squares_)
			flip_n_ls_bits(mask, board_size_);
	}

	unsigned int count_placements() const
	{
		unsigned int n = 0;
		count_next(n);
		return n;
	}

private:
	void count_next(unsigned int& n_placements, Mask col_mask = 0, Mask udiag_mask = 0,
					Mask ldiag_mask = 0, std::size_t col = 0) const
	{
		auto mask = ~(col_mask | udiag_mask | ldiag_mask) & good_squares_[col];

		if (const auto next_col = col + 1; next_col == board_size_)
			n_placements += count_bits(mask);
		else
			while (mask)
			{
				const Mask row_mask = ls_set_bit(mask);

				const auto next_col_mask = col_mask | row_mask;
				const auto next_udiag_mask = (udiag_mask | row_mask) >> 1;
				const auto next_ldiag_mask = (ldiag_mask | row_mask) << 1;

				count_next(n_placements, next_col_mask, next_udiag_mask, next_ldiag_mask, next_col);

				mask -= row_mask;
			}
	}

private:
	const std::size_t board_size_;
	std::vector<Mask> good_squares_;
};

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::size_t board_size;
		if (!read(board_size) || board_size == 0)
			return false;

		assert(3 <= board_size && board_size <= 15);

		bad_squares_.clear();
		for (std::size_t col = 0; col < board_size; ++col)
		{
			Mask bad_column = 0;
			for (std::size_t row = 0; row < board_size; ++row)
			{
				char c;
				read(c);
				set_bit(bad_column, row, c == '*');
			}
			bad_squares_.push_back(bad_column);
		}

		return true;
	}

	virtual void solve(unsigned int i_case) override
	{
		N_queens queens(bad_squares_);
		write_ln("Case ", i_case, ": ", queens.count_placements());
	}

private:
	std::vector<Mask> bad_squares_;
};

MAIN

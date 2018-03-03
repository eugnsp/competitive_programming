/*********************************************************************
Another n-queen problem
-----------------------
UVa ID: 11195

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "bit.hpp"
#include "util.hpp"
#include <cassert>
#include <vector>

using Coord = unsigned int;
using Mask = unsigned int;

class N_queens
{
private:
	using Board = std::vector<Coord>;

public:
	N_queens(const std::vector<Mask>& bad_squares)
		: good_squares_(bad_squares), board_size_(static_cast<Coord>(bad_squares.size()))
	{
		// Convert bad squares into good ones
		for (Mask& mask : good_squares_)
			flip_n_ls_bits(mask, board_size_);
	}

	unsigned int n_placements() const
	{
		unsigned int n = 0;
		count_next(0, 0, 0, 0, n);
		return n;
	}

private:
	void count_next(Mask col_mask, Mask udiag_mask, Mask ldiag_mask,
		Coord col, unsigned int& n_placements) const
	{
		auto mask = ~(col_mask | udiag_mask | ldiag_mask) & good_squares_[col];

		const auto next_col = col + 1;
		if (next_col == board_size_)
			n_placements += count_bits(mask);
		else
			while (mask)
			{
				const Mask row_mask = ls_set_bit(mask);

				const auto next_col_mask = col_mask | row_mask;
				const auto next_udiag_mask = (udiag_mask | row_mask) >> 1;
				const auto next_ldiag_mask = (ldiag_mask | row_mask) << 1;

				count_next(next_col_mask, next_udiag_mask, next_ldiag_mask,
					next_col, n_placements);

				mask -= row_mask;
			}
	}

private:
	std::vector<Mask> good_squares_;
	const Coord board_size_;
};

class CP : public CP2
{
private:
	virtual bool read_input(std::istream& in) override
	{
		Coord board_size;

		in >> board_size;
		if (board_size == 0)
			return false;

		assert(between(board_size, 3, 15));

		bad_squares_.clear();
		for (std::size_t col = 0; col < board_size; ++col)
		{
			Mask bad_column = 0;
			for (std::size_t row = 0; row < board_size; ++row)
			{
				char c;
				in >> c;
				set_bit(bad_column, row, c == '*');
			}
			bad_squares_.push_back(bad_column);
		}

		return true;
	}

	virtual void solve(std::ostream& out, std::size_t i_case) const override
	{
		N_queens queens(bad_squares_);
		out << "Case " << i_case + 1 << ": " << queens.n_placements() << '\n';
	}

private:
	std::vector<Mask> bad_squares_;
};

int main()
{
	CP p;
	return p.run();
}

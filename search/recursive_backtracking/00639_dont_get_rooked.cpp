/*********************************************************************
Don't get rooked
----------------
UVa ID: 006 39

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cassert>

using Coord = unsigned int;
using Board = Matrix<bool, Coord>;
using Pos = Position<Coord>;

class Dont_get_rooked
{
public:
	Dont_get_rooked(const Board& walls) : walls_(walls),
		width_(walls_.cols()), height_(walls.rows())
	{ }

	unsigned int max_n_rooks() const
	{
		Board empty_board(height_, width_, false);
		return max_n_rooks(empty_board, {0, 0});
	}

private:
	unsigned int max_n_rooks(Board& board, Pos pos) const
	{
		unsigned int max_n = 0;
		while (is_inside(pos))
		{
			if (can_be_placed(board, pos))
			{
				board(pos) = true;
				const auto n = max_n_rooks(board, next_pos(pos)) + 1;
				if (max_n < n)
					max_n = n;

				board(pos) = false;
			}
			pos = next_pos(pos);
		}

		return max_n;
	}

	bool can_be_placed(const Board& board, Pos pos) const
	{
		assert(is_inside(pos));

		if (walls_(pos))
			return false;

		return no_rook_in_direction(board, pos, {1, 0})
			&& no_rook_in_direction(board, pos, {0, 1})
			&& no_rook_in_direction(board, pos, {static_cast<Coord>(-1), 0})
			&& no_rook_in_direction(board, pos, {0, static_cast<Coord>(-1)});
	}

	bool no_rook_in_direction(const Board& board, Pos pos, Pos dir) const
	{
		while (is_inside(pos) && !walls_(pos))
		{
			if (board(pos))
				return false;

			pos += dir;
		}

		return true;
	}

	Pos next_pos(Pos pos) const
	{
		if (++pos.row >= height_)
		{
			pos.row = 0;
			++pos.col;
		}

		return pos;
	}

	bool is_inside(Pos pos) const
	{
		return pos.row < height_ && pos.col < width_;
	}

private:
	const Board& walls_;
	const Coord width_;
	const Coord height_;
};

class CP : public CP2
{
private:
	virtual bool read_input(std::istream& in) override
	{
		Coord n;
		in >> n;
		if (n == 0)
			return false;

		walls_.resize(n, n);
		read_matrix<char>(in, walls_, [](char c) { return c == 'X'; });

		return true;
	}

	virtual void solve(std::ostream& out, unsigned int) const override
	{
		const Dont_get_rooked rooks(walls_);
		out << rooks.max_n_rooks() << '\n';
	}

private:
	Board walls_;
};

int main()
{
	CP p;
	return p.run();
}

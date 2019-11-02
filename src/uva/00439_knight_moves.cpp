/*********************************************************************
Knight moves
------------
UVa ID: 004 39

A friend of you is doing research on the Traveling Knight Problem
where you are to find theshortest closed tour of knight moves that
visits each square of a given set of n squares on a chessboard exactly
once. He thinks that the most difficult part of the problem is
determining the smallest number of knight moves between two given
squares and that, once you have accomplished this, finding the tour
would be easy. Of course you know that it is vice versa. So you offer
him to write a program that solves the "difficult" part. Your job is
to write a program that takes two squares a and b as input and then
determines the number of knight moves on a shortest route from a to b.

Input
-----
The input file will contain one or more test cases. Each test case
consists of one line containing two squares separated by one space.
A square is a string consisting of a letter (a..h) representing the
column and a digit (1..8) representing the row on the chessboard.

Output
------
For each test case, print one line saying
	To get from xx to yy takes n knight moves.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cassert>
#include <cstddef>
#include <queue>
#include <string>

class Knight
{
public:
	Knight(std::size_t width, std::size_t height) : width_(width), height_(height)
	{}

	std::size_t count_moves(const Position from, const Position to) const
	{
		assert(is_valid_pos(from));
		assert(is_valid_pos(to));

		Matrix<std::size_t> depths(width_, height_, depth_unvisited);

		return bfs_find(from, depths, [&to](const Position pos) { return pos == to; });
	}

private:
	bool is_valid_pos(const Position pos) const
	{
		return pos.row < width_ && pos.col < height_;
	}

	template<class Fn>
	void for_all_knight_moves(const Position from, Fn&& fn) const
	{
		constexpr Position knight_moves[] = {
			{2, 1}, {1, 2}, {-1, 2}, {-2, 1}, {-2, -1}, {-1, -2}, {1, -2}, {2, -1}};
		for (const auto& m : knight_moves)
		{
			const auto to = from + m;
			if (is_valid_pos(to) && fn(to))
				break;
		}
	}

	template<class Fn>
	std::size_t bfs_find(const Position from, Matrix<std::size_t>& depths, Fn&& fn) const
	{
		if (fn(from))
			return 0;

		std::queue<Position> queue;
		queue.push(from);
		depths(from) = 0;

		while (!queue.empty())
		{
			const auto pos = queue.front();
			queue.pop();

			bool found = false;
			for_all_knight_moves(pos, [&](const Position to) {
				if (fn(to))
				{
					found = true;
					return true;
				}
				if (depths(to) == depth_unvisited)
				{
					depths(to) = depths(pos) + 1;
					queue.push(to);
				}
				return false;
			});

			if (found)
				return depths(pos) + 1;
		}

		return depth_unvisited;
	}

private:
	static constexpr auto depth_unvisited = static_cast<std::size_t>(-1);

	const std::size_t width_;
	const std::size_t height_;
};

std::string to_string(const Position pos)
{
	return std::string{static_cast<char>('a' + pos.row), static_cast<char>('1' + pos.col)};
}

Position from_string(const std::string& pos)
{
	assert(pos.length() == 2);
	return Position{pos[0] - 'a', pos[1] - '1'};
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::string from, to;
		if (!read(from, to))
			return false;

		from_ = from_string(from);
		to_ = from_string(to);

		return true;
	}

	virtual void solve(unsigned int) override
	{
		constexpr std::size_t board_size = 8;
		Knight knight(board_size, board_size);
		const auto n = knight.count_moves(from_, to_);

		write_ln("To get from ", to_string(from_), " to ", to_string(to_), " takes ", n,
			" knight moves.");
	}

private:
	Position from_, to_;
};

MAIN

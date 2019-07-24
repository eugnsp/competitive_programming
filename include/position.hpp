// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <cstddef>
#include <utility>

template<typename I = std::size_t>
struct Position
{
	using Type = I;

	I row = 0;
	I col = 0;

	Position() = default;

	constexpr Position(I row, I col) : row(row), col(col)
	{}

	Position& operator+=(const Position& pos)
	{
		row += pos.row;
		col += pos.col;
		return *this;
	}

	Position& operator-=(const Position& pos)
	{
		row -= pos.row;
		col -= pos.col;
		return *this;
	}
};

template<typename I>
bool operator==(const Position<I>& pos1, const Position<I>& pos2)
{
	return pos1.row == pos2.row && pos1.col == pos2.col;
}

template<typename I>
bool operator!=(const Position<I>& pos1, const Position<I>& pos2)
{
	return !(pos1 == pos2);
}

template<typename I>
bool operator<(const Position<I>& pos1, const Position<I>& pos2)
{
	return std::make_pair(pos1.row, pos1.col) < std::make_pair(pos2.row, pos2.col);
}

template<typename I>
Position<I> operator+(Position<I> pos1, const Position<I>& pos2)
{
	return (pos1 += pos2);
}

template<typename I>
Position<I> operator-(Position<I> pos1, const Position<I>& pos2)
{
	return (pos1 -= pos2);
}

template<typename I>
bool read(Position<I>& pos)
{
	return read(pos.row, pos.col);
}

#pragma once
#include <utility>

template<typename I>
struct Position
{
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

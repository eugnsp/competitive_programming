#pragma once

template<typename I>
struct Position
{
	I row;
	I col;

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
Position<I> operator+(Position<I> pos1, const Position<I>& pos2)
{
	return (pos1 += pos2);
}

template<typename I>
Position<I> operator-(Position<I> pos1, const Position<I>& pos2)
{
	return (pos1 -= pos2);
}

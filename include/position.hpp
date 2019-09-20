// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include "io.hpp"
#include <cstddef>
#include <utility>

struct Position
{
	std::size_t row = 0;
	std::size_t col = 0;

	Position() = default;

	template<typename T1, typename T2>
	constexpr Position(T1 row, T2 col) : row(static_cast<std::size_t>(row)), col(static_cast<std::size_t>(col))
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

	// Converts one-based indices to zero-based ones
	void to_zero_based()
	{
		--row;
		--col;
	}
};

inline bool operator==(const Position& pos1, const Position& pos2)
{
	return pos1.row == pos2.row && pos1.col == pos2.col;
}

inline bool operator!=(const Position& pos1, const Position& pos2)
{
	return !(pos1 == pos2);
}

inline bool operator<(const Position& pos1, const Position& pos2)
{
	return std::make_pair(pos1.row, pos1.col) < std::make_pair(pos2.row, pos2.col);
}

inline Position operator+(Position pos1, const Position& pos2)
{
	return (pos1 += pos2);
}

inline Position operator-(Position pos1, const Position& pos2)
{
	return (pos1 -= pos2);
}

inline bool read(Position& pos)
{
	return read(pos.row, pos.col);
}

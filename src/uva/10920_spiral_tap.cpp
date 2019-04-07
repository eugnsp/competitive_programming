/*********************************************************************
Spiral Tap
----------
UVa ID: 109 20

The game of Spiral Tap is played on a square grid. Pieces are placed
on a grid and the moves are realized according to the position of the
pieces on the grid. However, the coordinate system in the game of
Spiral Tap are a bit different that those find intraditional board
games, such as chess. The cell numbering scheme follow a spiral,
starting from the center of the grid in an anti-clockwise fashion:
13 12 11 10 25
14  3  2  9 24
15  4  1  8 23
16  5  6  7 22
17 18 19 20 21
The goal is, given the spiral tap coordinates of a cell, find its
cartesian coordinates (line 1 is at the bottom, and column 1 is
the leftmost).

Input
-----
The input is a series of lines. Each line is composed of two numbers:
SZ and P. SZ is the size of the border of the grid and is an odd number
no larger than 100'000. P is the spiral position of a cell in this
grid. The line such that SZ = P = 0 marks the end of the input (and is
not part of the data set).

Output
------
For each line in the data set of the input, your program must echo
a line "Line = X, column = Y.", where X and Y are the cartesian
coordinates of the corresponding cell.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "position.hpp"
#include <cassert>
#include <cmath>
#include <cstddef>

template<typename T>
Position<T> pos_in_spiral_traversal(T size, T index)
{
	if (index == 0)
		return {size / 2, size / 2};

	const auto r = (1 + static_cast<T>(std::sqrt(index))) / 2;
	const auto ns = 2 * r;
	const auto first = (ns - 1) * (ns - 1);

	const auto spr = size / 2 + r;
	const auto smr = size / 2 - r;

	assert(index >= first);
	auto offset = index - first;

	if (offset < ns)
		return {spr, spr - offset - 1};
	offset -= ns;
	if (offset < ns)
		return {spr - offset - 1, smr};
	offset -= ns;
	if (offset < ns)
		return {smr, smr + offset + 1};
	offset -= ns;
	return {smr + offset + 1, spr};
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(size_, index_) && size_ > 0;
	}

	virtual void solve(unsigned int) override
	{
		const auto pos = pos_in_spiral_traversal(size_, index_ - 1);		// To zero-based indexing
		write_ln("Line = ", pos.row + 1, ", column = ", pos.col + 1, '.');	// To one-based indexing
	}

private:
	std::size_t size_;
	std::size_t index_;
};



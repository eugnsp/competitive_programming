/*********************************************************************
Count on Cantor
---------------
UVa ID: 002 64

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "bit.hpp"
#include "util.hpp"
#include <cassert>
#include <utility>

using T = unsigned int;

// Returns the integer part of the square root of (n)
T isqrt(T n)
{
	assert(n > 0);

	T x = static_cast<T>(1) << (ms_set_bit_pos(n) / 2);
	T nx = (x + n / x) / 2;
	do
		x = exchange(nx, (nx + n / nx) / 2);
	while (x != nx && x + 1 != nx);

	return x;
}

std::pair<T, T> cantor(T index)
{
	assert(index >= 1);

	const auto d = (1 + isqrt(8 * index - 7)) / 2;
	const auto i = index - d * (d - 1) / 2;

	if (d % 2 == 0)
		return {i, d - i + 1};
	else
		return {d - i + 1, i};
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(index_);
	}

	virtual void solve(unsigned int) override
	{
		const auto c = cantor(index_);
		write_ln("TERM ", index_, " IS ", c.first, '/', c.second);
	}

private:
	T index_;
};

MAIN

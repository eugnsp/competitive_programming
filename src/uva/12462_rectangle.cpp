/*********************************************************************
Rectangle
---------
UVa ID: 124 62

A histogramis a polygon composed of a sequence of rectangular bars
aligned at a common base line. All bars have equal widths but may have
different integer heights. Additionally, each bar is fully colored
with a single color. There are a lot of rectangles that can be placed
inside this histogram (infinitely many, in fact). We will say that a
rectangle is nice if and only if:
	* It lies completely inside the histogram.
	* It covers one or several regions of positive area for every
	  color in the histogram (barely touching an area is not enough;
	  the total area covered for each color must be strictly positive).
In this problem, you are given a histogram and your task is to compute
the maximum area of all the possible nice rectangles.

Input
-----
The input contains several test cases (at most 50). Each test case is
described by several lines. The first line contains two integer N and
C, the number of bars and the total number of colors in the histogram,
respectively (1 <= N <= 10^5 and 1 <= C <= min(30; N)).The following
line contains N integers hi, the height of the i-th bar from left to
right (1 <= hi <= 10^9). The following line contains N integers ci,
the color of the i-th bar from left to right. Each color is
represented as an integer between 0 and C-1, inclusive. You can assume
that for each histogram there will be at least one bar of every color.
The last line of the input contains two zeros and should not be
processed.

Output
------
For each test case, output a single integer on a single line - the
area of the largest nice rectangle for this histogram.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <climits>
#include <cstddef>
#include <cstdint>
#include <stack>
#include <vector>

struct Height_and_colour
{
	using Mask = std::uint32_t;
	using Height = unsigned long long;

	Height height;
	Mask colour_mask;
};

Height_and_colour::Height max_colour_histogram_area(
	std::vector<Height_and_colour>& heights_and_colours, unsigned int n_colours)
{
	assert(1 <= n_colours && n_colours < CHAR_BIT * sizeof(Height_and_colour::Mask));

	const auto n = heights_and_colours.size();
	const auto all_colours_mask = (static_cast<Height_and_colour::Mask>(1) << n_colours) - 1;

	std::stack<std::size_t> smallers;
	Height_and_colour::Height max_area = 0;

	std::size_t i = 0;
	while (i != n || !smallers.empty())
	{
		Height_and_colour::Mask mask = 0;

		while (!smallers.empty() && (i == n || heights_and_colours[i].height <
												   heights_and_colours[smallers.top()].height))
		{
			const auto height = heights_and_colours[smallers.top()].height;
			const auto colour_mask = heights_and_colours[smallers.top()].colour_mask;
			smallers.pop();

			mask |= colour_mask;
			if (i != n)
				heights_and_colours[i].colour_mask |= colour_mask;

			if (mask == all_colours_mask)
			{
				const auto width = smallers.empty() ? i : i - smallers.top() - 1;
				const auto area = static_cast<Height_and_colour::Height>(height * width);
				max_area = std::max(max_area, area);
			}
		}
		if (i != n)
			smallers.push(i++);
	}

	return max_area;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::size_t n_bars;
		if (!read(n_bars) || n_bars == 0)
			return false;

		read(n_colours_);
		assert(n_colours_ < CHAR_BIT * sizeof(Height_and_colour::Mask));

		heights_and_colours_.resize(n_bars);
		for (auto& hc : heights_and_colours_)
			read(hc.height);
		for (auto& hc : heights_and_colours_)
		{
			unsigned int colour;
			read(colour);
			hc.colour_mask = static_cast<Height_and_colour::Mask>(1) << colour;
		}

		return true;
	}

	virtual void solve(unsigned int) override
	{
		write_ln(max_colour_histogram_area(heights_and_colours_, n_colours_));
	}

private:
	std::vector<Height_and_colour> heights_and_colours_;
	unsigned int n_colours_;
};

MAIN

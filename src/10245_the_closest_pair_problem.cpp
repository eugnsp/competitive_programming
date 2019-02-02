/*********************************************************************
The closest pair problem
------------------------
UVa ID: 102 45

Given a set of points in a two dimensional space, you will have to
find the distance between the closest two points.

Input
-----
The input file contains several sets of input. Each set of input
starts with an integer N (0 <= N <= 10'000), which denotes the
number of points in this set. The next N lines contains the
coordinates of N two-dimensional points. The first of the two
numbers denotes the X-coordinate and the latter denotes the
Y-coordinate. The input is terminated by a set whose N = 0. This
set should not be processed. The value of the coordinates will be
less than 40'000 and non-negative.

Output
------
For each set of input produce a single line of output containing
a floating point number (with four digits after the decimal point)
which denotes the distance between the closest two points. If there
is no such two points in the input whose distance is less than
10'000, print the line 'INFINITY'.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "point.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cmath>
#include <iomanip>
#include <limits>
#include <numeric>
#include <vector>

using Coord = double;
using Pt = Point<Coord>;

template<class It>
double min_dist_sq_direct(It first, It last)
{
	auto d_sq = std::numeric_limits<double>::max();
	for (auto it1 = first; it1 != last; ++it1)
		for (auto it2 = first; it2 != it1; ++it2)
			d_sq = std::min(d_sq, distance_sq(*it1, *it2));

	return d_sq;
}

template<class It_x, class It_y>
double min_dist_sq_impl(It_x first_x, It_y first_y, std::size_t size)
{
	assert(std::is_sorted(first_x, first_x + size, less_xy<Coord>));
	assert(std::is_sorted(
		first_y, first_y + size, [](It_x it1, It_x it2) { return less_yx(*it1, *it2); }));

	if (size <= 10)
		return min_dist_sq_direct(first_x, first_x + size);

	const auto mid_x = first_x + size / 2;

	// Split
	std::vector<It_x> pts_y1, pts_y2;
	pts_y1.reserve(mid_x - first_x);
	pts_y2.reserve(first_x + size - mid_x);
	for (auto pt = first_y; pt != first_y + size; ++pt)
		(*pt < mid_x ? pts_y1 : pts_y2).push_back(*pt);

	// Divide
	const auto d1 = min_dist_sq_impl(first_x, pts_y1.begin(), pts_y1.size());
	const auto d2 = min_dist_sq_impl(mid_x, pts_y2.begin(), pts_y2.size());
	auto d = std::min(d1, d2);

	// Conquer
	const auto xm = mid_x->x;

	std::vector<Pt> pts_in_strip;
	for (auto it = first_y; it != first_y + size; ++it)
	{
		auto delta = (*it)->x - xm;
		if (delta * delta < d)
			pts_in_strip.push_back(**it);
	}

	assert(std::is_sorted(pts_in_strip.begin(), pts_in_strip.end(), less_yx<Coord>));

	constexpr auto max_pts_in_rect = 8;
	for (auto it1 = pts_in_strip.begin(); it1 != pts_in_strip.end(); ++it1)
		for (auto it2 = it1 + 1; it2 != pts_in_strip.end() && it2 - it1 <= max_pts_in_rect; ++it2)
		{
			const auto dy = it2->y - it1->y;
			assert(dy >= 0);
			if (dy * dy >= d)
				break;

			d = std::min(d, distance_sq(*it1, *it2));
		}

	return d;
}

double min_dist(std::vector<Pt> pts)
{
	using It = std::vector<Pt>::iterator;

	std::sort(pts.begin(), pts.end(), less_xy<Coord>);

	std::vector<It> pts_y(pts.size());
	std::iota(pts_y.begin(), pts_y.end(), pts.begin());
	std::sort(pts_y.begin(), pts_y.end(), [](It p1, It p2) { return less_yx(*p1, *p2); });

	return std::sqrt(min_dist_sq_impl(pts.begin(), pts_y.begin(), pts.size()));
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_size_vec(points_);
	}

	virtual void solve(unsigned int) override
	{
		const auto md = min_dist(std::move(points_));

		if (md >= 10'000)
			write_ln("INFINITY");
		else
			write_ln(std::setprecision(4), std::fixed, md);
	}

private:
	std::vector<Pt> points_;
};

MAIN(CP)

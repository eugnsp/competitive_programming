/*********************************************************************
Moth eradication
----------------
UVa ID: 218

Entomologists in the Northeast have set out traps to determine the
influx of Jolliet moths into the area. They plan to study eradication
programs that have some potential to control the spread of the moth
population. The study calls for organizing the traps in which moths
have been caught into compact regions, which will then be used to test
each eradication program. A region is defined as the polygon with the
minimum length perimeter that can enclose all traps within that region.
You must write a program that can take as input the locations of traps
in a region and output the locations of traps that lie on the
perimeter of the region as well as the length of the perimeter.

Input
-----
The input file will contain records of data for several regions. The
first line of each record contains the number (an integer) of traps
for that region. Subsequent lines of the record contain 2 real numbers
that are the x- and y-coordinates of the trap locations. Data within a
single record will not be duplicated. End of input is indicated by a
region with 0 traps.

Output
------
Output for a single region is displayed on at least 3 lines:
First line: The number of the region. (The first record corresponds
to Region #1, the second to Region #2, etc.)
Next line(s): A listing of all the points that appear on the perimeter
of the region. The points must be identified in the standard form
"(x-coordinate,y-coordinate)" rounded to a single decimal place. The
starting point for this listing is irrelevant, but the listing must be
oriented clockwise and begin and end with the same point. For collinear
points, any order which describes the minimum length perimeter is
acceptable.
Last line: The length of the perimeter of the region rounded to 2
decimal places. One blank line must separate output from consecutive
input records.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "point.hpp"
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <vector>

using T = double;
using Points = std::vector<Point<T>>;

bool is_colinear(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3)
{
	return cross(p3 - p1, p2 - p1) == 0;
}

bool is_left_turn(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3)
{
	return cross(p3 - p1, p2 - p1) < 0;
}

Points convex_hull(Points points)
{
	if (points.size() < 3)
		return points;

	std::sort(points.begin(), points.end());

	auto p = points.begin();
	const auto p0 = *p++;

	// Sort points by polar angle in counter-clockwise order around (p0),
	// if more than one point has the same angle, the farthest one goes first
	std::sort(p, points.end(), [&p0](const Point<T>& p1, const Point<T>& p2)
	{
		const auto cr = cross(p1 - p0, p2 - p0);
		if (cr != 0)
			return cr > 0;
		return norm_sq(p2 - p0) < norm_sq(p1 - p0);
	});

	// For points with the same angle, remove all but the farthest one
	const auto last = std::unique(p, points.end(),
		[&p0](const Point<T>& p1, const Point<T>& p2) { return is_colinear(p0, p1, p2); });
	points.erase(last, points.end());

	if (points.size() < 3)
	{
		if (points.size() > 1 && points[0] == points[1])
			points.pop_back();

		return points;
	}

	Points vertices{p0, *p++, *p++};
	while (p != points.end())
	{
		while (!is_left_turn(*(vertices.end() - 2), vertices.back(), *p))
			vertices.pop_back();
		vertices.push_back(*p++);
	}

	assert(vertices.size() >= 3);
	return vertices;
}

template<class It>
double perimeter(const It first, const It last)
{
	if (first == last)
		return 0;

	double perimeter = 0;
	for (It it = first, next = std::next(it); it != last; ++it, ++next)
	{
		if (next == last)
			next = first;
		perimeter += distance(*it, *next);
	}

	return perimeter;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_size_vec(traps_);
	}

	virtual void solve(unsigned int i_case) override
	{
		if (i_case > 0)
			write_ln();

		write_ln("Region #", i_case + 1, ':');

		const auto border = convex_hull(traps_);

		write(std::fixed, std::setprecision(1));
		write_range(border.rbegin(), border.rend(), '-');
		write_ln('-', border.back());

		write(std::setprecision(2));
		write_ln("Perimeter length = ", perimeter(border.begin(), border.end()));
	}

private:
	std::vector<Point<T>> traps_;
};

MAIN(CP)

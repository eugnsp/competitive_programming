/*********************************************************************
New marketing plan
------------------
UVa ID: 112 57

You work at a company that produces circular plates. In a meeting,
your boss announces a new marketing plan - the company will package
the plates in specially shaped containers, so as to attract customers'
attention. The specially shaped containers will always be convex
polygon. The existing packaging software can easily compute the maximum
plate size for a given container size, but unfortunately, it can only
do so for rectangular containers. Therefore, your boss asks you to
write a program that can compute the maximum plate size given the
container's shape. Given the shape of a container, you need to compute
the radius of the largest possible plate which can be fitted inside
the container.

Input
-----
Input consists of multiple problem instances. Each instance
begins with a single positive integer n, where 3 <= n <= 50.
It is followed by 2n integers x1, y1, x2, y2, ..., xn; yn, where
-1000 <= xi, yi <= 1000 for all i. They indicate the shape of a
container which is a simple convex polygon with n vertices (x1, y1),
(x2, y2), ..., (xn, yn) in counter-clockwise order. The area of the
polygon is guaranteed to be positive and no three consecutive
vertices are collinear. The input data is terminated by an n being 0.
There will not be more than 100 test cases.

Output
------
For each test case, print out the radius of the largest possible plate
which can be fitted inside the input container. The answer should be
printed with 3 digits after the decimal point in a single line.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "static_matrix.hpp"
#include <cassert>
#include <cmath>
#include <iomanip>
#include <list>
#include <queue>
#include <vector>

using Point = std::pair<double, double>;

struct Side
{
	std::size_t index;

	// Each side has the line equation:
	// normal_x * x + normal_y * y + c = 0
	Point normal;
	double c;
};

using Sides = std::list<Side>;

struct Queue_element
{
	double time;
	Sides::const_iterator side;
	std::size_t index;

	bool operator<(const Queue_element& other) const
	{
		return other.time < time;
	}
};

using Queue = std::priority_queue<Queue_element>;

double dot(const Point& p1, const Point& p2)
{
	return p1.first * p2.first + p1.second * p2.second;
}

double cross(const Point& p1, const Point& p2)
{
	return p1.first * p2.second - p1.second * p2.first;
}

double distance(const Point& p1, const Point& p2)
{
	const auto dx = p1.first - p2.first;
	const auto dy = p1.second - p2.second;
	return std::sqrt(dx * dx + dy * dy);
}

Point linear_solve(const Matrix<double, 2, 2>& m, const Point& r)
{
	const auto det = m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0);
	return {cross(r, {m(0, 1), m(1, 1)}) / det,
			cross({m(0, 0), m(1, 0)}, r) / det};
}

double collapse_time(const Sides& sides, Sides::const_iterator side)
{
	const auto prev = std::prev(side != sides.begin() ? side : sides.end());
	const auto next = std::next(side) != sides.end() ? std::next(side) : sides.begin();

	const Matrix<double, 2, 2> m{side->normal.first - prev->normal.first,
								 side->normal.first - next->normal.first,
								 side->normal.second - prev->normal.second,
								 side->normal.second - next->normal.second};

	const auto rc = linear_solve(m, {prev->c - side->c, next->c - side->c});
	return dot(side->normal, rc) + side->c;
}

Queue make_initial_queue(const Sides& sides)
{
	Queue queue;

	std::size_t index = 0;
	for (auto side = sides.begin(); side != sides.end(); ++side)
		queue.push({collapse_time(sides, side), side, index++});

	return queue;
}

double inscribed_circle_radius(const std::vector<Point>& points)
{
	// Idea of the algorithm: https://stackoverflow.com/a/46877318/1625187

	std::list<Side> sides;

	std::size_t index = 0;
	for (auto curr = points.begin(), next = std::next(curr); curr != points.end(); ++curr, ++next)
	{
		if (next == points.end())
			next = points.begin();

		const auto d = distance(*curr, *next);
		const auto n = Point{(curr->second - next->second) / d, (next->first - curr->first) / d};
		const auto c = cross(*curr, *next) / d;
		sides.push_back({index++, n, c});
	}

	std::vector<bool> collapsed(points.size(), false);

	auto queue = make_initial_queue(sides);
	while (sides.size() >= 3)
	{
		const auto top = queue.top();
		queue.pop();
		if (collapsed[top.index])
			continue;

		collapsed[top.index] = true;

		const auto& side = top.side;
		const auto prev = std::prev(side != sides.begin() ? side : sides.end());
		const auto next = std::next(side) != sides.end() ? std::next(side) : sides.begin();
		sides.erase(side);

		const auto t_prev = collapse_time(sides, prev);
		const auto t_next = collapse_time(sides, next);

		queue.push({t_prev, prev, prev->index});
		queue.push({t_next, next, next->index});
	}

	while (!queue.empty() && collapsed[queue.top().index])
		queue.pop();

	assert(!queue.empty());
	return queue.top().time;
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
		const auto r = inscribed_circle_radius(points_);
		write_ln(std::fixed, std::setprecision(3), r);
	}

private:
	std::vector<Point> points_;
};

MAIN(CP)

/*********************************************************************
SCUD busters
------------
UVa ID: 001 09

Some problems are difficult to solve but have a simplification that is
easy to solve. Rather than deal with the difficulties of constructing
a model of the Earth (a somewhat oblate spheroid), consider a pre-
Columbian flat world that is a 500 kilometer x 500 kilometer square.
In the model used in this problem, the flat world consists of several
warring kingdoms. Though war like, the people of the world are strict
isolationists; each kingdom is surrounded by a high (but thin) wall
designed to both protect the kingdom and to isolate it. To avoid fights
for power, each kingdom has its own electric power plant. When the
urge to fight becomes too great, the people of a kingdom often launch
missiles at other kingdoms. Each missile that lands within the walls
of a kingdom destroys that kingdom's power plant (without loss of life).
Given coordinate locations of several kingdoms (by specifying the
locations of houses and the location of the power plant in a kingdom)
and missile landings you are to write a program that determines the
total area of all kingdoms that are without power after an exchange of
missile fire. In the simple world of this problem kingdoms do not
overlap. Furthermore, the walls surrounding each kingdom are considered
to be of zero thickness. The wall surrounding a kingdom is the minimal-
perimeter wall that completely surrounds all the houses and the power
station that comprise a kingdom; the area of a kingdom is the area
enclosed by the minimal-perimeter thin wall. There is exactly one
power station per kingdom. There may be empty space between kingdoms.

Input
-----
The input is a sequence of kingdom specifications followed by a
sequence of missile landing locations. A kingdom is specified by a
number N (3 <= N <= 100) on a single line which indicates the number of
sites in this kingdom. The next line contains the x and y coordinates
of the power station, followed by N-1 lines of x, y pairs indicating
the locations of homes served by this power station. A value of -1 for
N indicates that there are no more kingdoms. There will be at least one
kingdom in the dataset. Following the last kingdom specification will
be the coordinates of one or more missile attacks, indicating the
location of a missile landing. Each missile location is on a line by
itself. You are to process missile attacks until you reach the end of
the file. Locations are specified in kilometers using coordinates on
a 500 km by 500 km grid. All coordinates will be integers between 0
and 500 inclusive. Coordinates are specified as a pair of integers
separated by whitespace on a single line. The input file will consist
of up to 20 kingdoms, followed by any number of missile attacks.

Output
------
The output consists of a single number representing the total area
of all kingdoms without electricity after all missile attacks have
been processed. The number should be printed with (and correct to)
two decimal places.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "point.hpp"
#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <utility>
#include <vector>

using Pt = Point<int>;
using Pts = std::vector<Pt>;

class Convex_hull
{
public:
	Convex_hull(std::vector<Pt> points)
	{
		assert(points.size() >= 3);
		std::sort(points.begin(), points.end());

		auto p = points.begin();
		const auto p0 = *p++;

		// Sort points by the polar angle in counter-clockwise order around (p0),
		// if more than one point has the same angle, the farthest one goes first
		std::sort(p, points.end(), [&p0](const Pt& p1, const Pt& p2) {
			const auto cr = cross(p1 - p0, p2 - p0);
			if (cr != 0)
				return cr > 0;
			return norm_sq(p2 - p0) < norm_sq(p1 - p0);
		});

		// For points with the same angle, remove all but the farthest one
		const auto last = std::unique(
			p, points.end(), [&p0](const Pt& p1, const Pt& p2) { return is_colinear(p0, p1, p2); });
		points.erase(last, points.end());

		assert(points.size() >= 3);

		vertices_.assign({p0, *p++, *p++});
		while (p != points.end())
		{
			while (!is_left_turn(*(vertices_.end() - 2), vertices_.back(), *p))
				vertices_.pop_back();
			vertices_.push_back(*p++);
		}

		assert(vertices_.size() >= 3);
	}

	bool contains(const Pt& point) const
	{
		const auto n = vertices_.size();
		assert(n >= 3);

		for (std::size_t i = 0; i < n; ++i)
		{
			const auto& vi = vertices_[i];
			const auto& vj = vertices_[(i + 1) % n];

			if (is_right_turn(vi, vj, point))
				return false;
		}

		return true;
	}

	double area() const
	{
		double area = 0;

		const auto n = vertices_.size();
		for (std::size_t i = 0; i < n; ++i)
		{
			const auto& vi = vertices_[i];
			const auto& vj = vertices_[(i + 1) % n];

			area += vi.x * vj.y - vj.x * vi.y;
		}

		assert(area >= 0);
		return area / 2;
	}

private:
	static bool is_colinear(const Pt& p1, const Pt& p2, const Pt& p3)
	{
		return cross(p3 - p1, p2 - p1) == 0;
	}

	static bool is_left_turn(const Pt& p1, const Pt& p2, const Pt& p3)
	{
		return cross(p3 - p1, p2 - p1) < 0;
	}

	static bool is_right_turn(const Pt& p1, const Pt& p2, const Pt& p3)
	{
		return cross(p3 - p1, p2 - p1) > 0;
	}

private:
	std::vector<Pt> vertices_;
};

class CP : public CP3
{
private:
	virtual void read_input() override
	{
		int n_sites;
		while (read(n_sites) && n_sites > 0)
		{
			auto& sites = kingdoms_.emplace_back(Pts(n_sites));
			for (auto& s : sites)
				read(s);
		}

		Pt pt;
		while (read(pt))
			attacks_.push_back(pt);
	}

	virtual void solve() override
	{
		std::vector<std::pair<Convex_hull, bool>> kingdom_borders;
		for (const auto& k : kingdoms_)
			kingdom_borders.emplace_back(k, false);

		std::vector<bool> attacked(kingdoms_.size(), false);
		for (auto& k : kingdom_borders)
			for (const auto& a : attacks_)
				if (k.first.contains(a))
					k.second = true;

		double total_area = 0;
		for (const auto& k : kingdom_borders)
			if (k.second)
				total_area += k.first.area();

		write_ln(std::setprecision(2), std::fixed, total_area);
	}

private:
	std::vector<Pts> kingdoms_;
	Pts attacks_;
};

MAIN

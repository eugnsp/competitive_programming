/*********************************************************************
Cops and robbers
----------------
UVa ID: 003 61

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "point.hpp"
#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <vector>
#include <utility>

class CP : public CP2
{
private:
	using T = int;
	using Points = std::vector<Point<T>>;

	class Convex_hull
	{
	public:
		Convex_hull(Points points)
		{
			if (points.size() < 3)
				return;

			std::sort(points.begin(), points.end());

			auto p = points.begin();
			const auto p0 = *p++;

			// Sort points by polar angle in counter-clockwise order around (p0),
			// if more than one point has the same angle, the farthest one goes first
			std::sort(p, points.end(),
				[&p0](const Point<T>& p1, const Point<T>& p2)
				{
					const auto cr = cross(p1 - p0, p2 - p0);
					if (cr != 0)
						return cr > 0;
					return norm_sq(p2 - p0) < norm_sq(p1 - p0);
				});

			// For points with the same angle, remove all but the farthest one
			const auto last = std::unique(p, points.end(),
				[&p0](const Point<T>& p1, const Point<T>& p2)
				{
					return is_colinear(p0, p1, p2);
				});
			points.erase(last, points.end());

			if (points.size() < 3)
			{
				if (points.size() > 1 && points[0] == points[1])
					points.pop_back();

				vertices_ = std::move(points);
				return;
			}

			vertices_.assign({p0, *p++, *p++});
			for (; p != points.end(); ++p)
			{
				while (!is_left_turn(*(vertices_.end() - 2), vertices_.back(), *p))
					vertices_.pop_back();
				vertices_.push_back(*p);
			}

			assert(vertices_.size() >= 3);
		}

		bool contains(const Point<T>& point) const
		{
			const auto n = vertices_.size();
			assert(n != 0);
			
			if (n == 1)
				return point == vertices_.front();
			
			if (n == 2)
			{
				if (is_left_turn(vertices_[0], vertices_[1], point) ||
					is_right_turn(vertices_[0], vertices_[1], point))
					return false;

				return (between(point.x, vertices_[0].x, vertices_[1].x) &&
					between(point.y, vertices_[0].y, vertices_[1].y));
			}

			for (std::size_t i = 0; i < n; ++i)
			{
				const auto& vi = vertices_[i];
				const auto& vj = vertices_[(i + 1) % n];

				if (is_right_turn(vi, vj, point))
					return false;
			}

			return true;
		}

	private:
		static bool is_colinear(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3)
		{
			return cross(p3 - p1, p2 - p1) == 0;
		}

		static bool is_left_turn(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3)
		{
			return cross(p3 - p1, p2 - p1) < 0;
		}

		static bool is_right_turn(const Point<T>& p1, const Point<T>& p2, const Point<T>& p3)
		{
			return cross(p3 - p1, p2 - p1) > 0;
		}

	private:
		Points vertices_;
	};

private:
	virtual bool read_input() override
	{
		std::size_t n_cops, n_robbers, n_citizens;
		read(n_cops, n_robbers, n_citizens);

		if (n_cops == 0 && n_robbers == 0 && n_citizens == 0)
			return false;

		cops_.resize(n_cops);
		for (auto& c : cops_)
			read(c.x, c.y);

		robbers_.resize(n_robbers);
		for (auto& r : robbers_)
			read(r.x, r.y);

		citizens_.resize(n_citizens);
		for (auto& c : citizens_)
			read(c.x, c.y);

		return true;
	}

	virtual void solve(unsigned int i_case) override
	{
		const Convex_hull cops_border(cops_);
		const Convex_hull robbers_border(robbers_);

		write_ln("Data set ", i_case + 1, ':');
		for (auto& c : citizens_)
		{
			write("     Citizen at (", c.x, ',', c.y, ") is ");
			if (cops_.size() > 2 && cops_border.contains(c))
				write_ln("safe.");
			else if (robbers_.size() > 2 && robbers_border.contains(c))
				write_ln("robbed.");
			else
				write_ln("neither.");
		}

		write_ln();
	}

private:
	Points cops_, robbers_, citizens_;
};

MAIN(CP)

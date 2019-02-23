/*********************************************************************
SCUD busters
------------
UVa ID: 001 09

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "point.hpp"
#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <vector>

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
			assert(points.size() >= 3);
			std::sort(points.begin(), points.end());

			auto p = points.begin();
			const auto p0 = *p++;

			// Sort points by polar angle in counter-clockwise order around (p0),
			// if more than one point has the same angle, the farthest one goes first
			std::sort(p, points.end(), [&p0](const Point<T>& p1, const Point<T>& p2) {
				const auto cr = cross(p1 - p0, p2 - p0);
				if (cr != 0)
					return cr > 0;
				return norm_sq(p2 - p0) < norm_sq(p1 - p0);
			});

			// For points with the same angle, remove all but the farthest one
			const auto last =
				std::unique(p, points.end(), [&p0](const Point<T>& p1, const Point<T>& p2) {
					return is_colinear(p0, p1, p2);
				});
			points.erase(last, points.end());

			assert(points.size() >= 3);

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
		// 		CHECK
		//		if (!in)
		//			return false;

		int n_sites;
		while (read(n_sites) && n_sites > 0)
		{
			assert(between(n_sites, 3, 100));
			Points sites(n_sites);
			for (auto& s : sites)
				read(s.x, s.y);
			kingdoms_.push_back(std::move(sites));
		}

		T x, y;
		while (read(x, y))
			attacks_.emplace_back(x, y);

		return true;
	}

	virtual void solve(unsigned int) override
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
	std::vector<Points> kingdoms_;
	Points attacks_;
};

MAIN(CP)
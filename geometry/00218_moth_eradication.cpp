/*********************************************************************
Moth eradication
----------------
UVa ID: 218

Goal:	find all the points that appear on the perimeter of the region
		and its perimeter.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "point.hpp"
#include <algorithm>
#include <cassert>
#include <iomanip>
#include <vector>

class Moth_eradication : public CP2
{
private:
	using T = double;
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
					return length_sq(p2 - p0) < length_sq(p1 - p0);
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

		const Points& vertices() const
		{
			return vertices_;
		}

		double perimeter() const
		{
			double perimeter = 0;

			const auto n = vertices_.size();
			for (std::size_t i = 0; i < n; ++i)
			{
				const auto& vi = vertices_[i];
				const auto& vj = vertices_[(i + 1) % n];
				perimeter += distance(vi, vj);
			}

			return perimeter;
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

	private:
		Points vertices_;
	};

private:
	virtual bool read_input(std::istream& in) override
	{
		// <x_1> <y_1>
		// ...
		// <x_n> <y_n>

		std::size_t n_traps;
		in >> n_traps;

		if (n_traps == 0)
			return false;

		traps_.resize(n_traps);
		for (auto& t : traps_)
			in >> t.x >> t.y;

		return true;
	}

	virtual void solve(std::ostream& out, std::size_t i_case) override
	{
		const Convex_hull border(traps_);

		if (i_case > 0)
			out << '\n';

		out << "Region #" << i_case + 1 << ":\n";
		
		out << std::setprecision(1) << std::fixed;
		for (auto p = border.vertices().rbegin(); p != border.vertices().rend(); ++p)
			out << '(' << p->x << ',' << p->y << ")-";
		out << '(' << border.vertices().rbegin()->x << ',' << border.vertices().rbegin()->y << ")\n";
		
		out << "Perimeter length = " << std::setprecision(2) << border.perimeter() << '\n';
	}

private:
	std::vector<Point<T>> traps_;
};

int main()
{
	Moth_eradication p;
	return p.run();
}

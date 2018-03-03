/*********************************************************************
Water falls
-----------
UVa ID: 833

Goal:	find the largest number of points that all lie on one line.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "point.hpp"
#include "util.hpp"
#include <cassert>
#include <vector>
#include <utility>

class Water_falls : public CP1
{
private:
	using T = int;

	using Segment = std::pair<Point<T>, Point<T>>;

private:
	virtual void read_input(std::istream& in) override
	{
		// <number of segments = n>
		// <x_start_1> <y_start_1> <x_end_1> <y_end_1>
		// ...
		// <x_start_n> <y_start_n> <x_end_n> <y_end_n>
		// <number of sources = k>
		// <x_1> <y_1>
		// ...
		// <x_k> <y_k>

		std::size_t n_segments;
		in >> n_segments;

		segments_.resize(n_segments);
		for (auto& s : segments_)
		{
			in >> s.first.x >> s.first.y >> s.second.x >> s.second.y;
			assert(s.first.y != s.second.y);
		}

		std::size_t n_sources;
		in >> n_sources;

		sources_.resize(n_sources);
		for (auto& s : sources_)
			in >> s.x >> s.y;
	}

	virtual void solve(std::ostream& out, std::size_t i_case) override
	{
		if (i_case > 0)
			out << '\n';
		for (const auto& source : sources_)
			out << falling_point(source) << '\n';
	}

	T falling_point(const Point<T>& source)
	{
		double max_y = 0;
		auto target = segments_.end();
		for (auto s = segments_.begin(); s != segments_.end(); ++s)
		{
			const auto& p1 = s->first;
			const auto& p2 = s->second;

			if (!between(source.x, p1.x, p2.x))
				continue;

			auto y = static_cast<double>(p1.y - p2.y) / (p1.x - p2.x)
				* (source.x - p1.x) + p1.y;

			if (y < source.y && y > max_y)
			{
				target = s;
				max_y = y;
			}
		}

		if (target == segments_.end())
			return source.x;
		else
			return falling_point(target->first.y < target->second.y ? target->first : target->second);
	}

private:
	std::vector<Segment> segments_;
	std::vector<Point<T>> sources_;
};

int main()
{
	Water_falls p;
	return p.run();
}

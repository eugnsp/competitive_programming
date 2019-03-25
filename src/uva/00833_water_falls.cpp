/*********************************************************************
Water falls
-----------
UVa ID: 008 33

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "point.hpp"
#include "util.hpp"
#include <cassert>
#include <vector>
#include <utility>

class CP : public CP1
{
private:
	using T = int;

	using Segment = std::pair<Point<T>, Point<T>>;

private:
	virtual void read_input() override
	{
		std::size_t n_segments;
		read(n_segments);

		segments_.resize(n_segments);
		for (auto& s : segments_)
		{
			read(s.first.x, s.first.y, s.second.x, s.second.y);
			assert(s.first.y != s.second.y);
		}

		std::size_t n_sources;
		read(n_sources);

		sources_.resize(n_sources);
		for (auto& s : sources_)
			read(s.x, s.y);
	}

	virtual void solve(unsigned int i_case) override
	{
		if (i_case > 1)
			write_ln();
		for (const auto& source : sources_)
			write_ln(falling_point(source));
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

			auto y = static_cast<double>(p1.y - p2.y) / (p1.x - p2.x) * (source.x - p1.x) + p1.y;

			if (y < source.y && y > max_y)
			{
				target = s;
				max_y = y;
			}
		}

		if (target == segments_.end())
			return source.x;
		else
			return falling_point(
				target->first.y < target->second.y ? target->first : target->second);
	}

private:
	std::vector<Segment> segments_;
	std::vector<Point<T>> sources_;
};



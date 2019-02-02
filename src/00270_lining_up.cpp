/*********************************************************************
Lining up
---------
UVa ID: 270

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "point.hpp"
#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <string>
#include <sstream>
#include <vector>

class CP : public CP1
{
private:
	using T = int;

private:
	virtual void read_input() override
	{
		points_.clear();

		std::string coords_str;
		while (read_ln(coords_str))
		{
			if (coords_str.empty())
			{
				if (points_.empty())
					continue;
				break;
			}

			std::istringstream coords(coords_str);
			T x, y;
			coords >> x >> y;
			points_.emplace_back(x, y);
		}

		assert(between(points_.size(), 2, 700));
	}

	virtual void solve(unsigned int i_case) override
	{
		/*********************************************************************
		For each point, shift the origin to that point and find the maximum
		number of points that all have the same polar angle mod pi.
		**********************************************************************/

		std::vector<Point<T>> other_points;

		std::size_t n_points_max = 0;
		for (auto pivot = points_.cbegin(); pivot != points_.cend(); ++pivot)
		{
			other_points.resize(pivot - points_.cbegin());
			std::transform(points_.cbegin(), pivot, other_points.begin(), [&pivot](Point<T> p) {
				p -= *pivot;
				p /= gcd(p.x, p.y);
				return p;
			});

			std::sort(other_points.begin(), other_points.end());
			const std::size_t n_points =
				1 + max_adjacent_n(other_points.begin(), other_points.end());
			n_points_max = std::max(n_points_max, n_points);
		}

		if (i_case > 0)
			write_ln();
		write_ln(n_points_max);
	}

	// Returns the maximum number of consecutive identical elements
	template<class It>
	static std::size_t max_adjacent_n(It begin, It end)
	{
		if (begin == end)
			return 0;

		std::size_t max_n = 1;
		std::size_t n = 1;
		for (auto prev = begin++; begin != end; ++begin)
		{
			if (*begin == *prev)
				max_n = std::max(max_n, ++n);
			else
			{
				prev = begin;
				n = 1;
			}
		}

		return max_n;
	}

private:
	std::vector<Point<T>> points_;
};

MAIN(CP)
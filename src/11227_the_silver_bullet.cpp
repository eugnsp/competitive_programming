/*********************************************************************
The silver bullet
-----------------
UVa ID: 112 27

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "point.hpp"
#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

class CP : public CP1
{
private:
	using T = int;

	class Direction
	{
	public:
		Direction(const Point<T>& p)
			: x_(p.x), y_(p.y)
		{
			const auto d = gcd(x_, y_);
			x_ /= d;
			y_ /= d;
		}

		bool operator<(const Direction& d) const
		{
			if (x_ != d.x_)
				return x_ < d.x_;
			return y_ < d.y_;
		}

		bool operator==(const Direction& d) const
		{
			return x_ == d.x_ && y_ == d.y_;
		}

	private:
		T x_;
		T y_;
	};

private:
	virtual void read_input() override
	{
		std::size_t n_gnus;
		read(n_gnus);

		gnus_.resize(n_gnus);
		for (auto& g : gnus_)
		{
			double x, y;
			read(x, y);
			x *= 100;
			y *= 100;
			g.x = static_cast<T>(x);
			g.y = static_cast<T>(y);
		}

		assert(between(gnus_.size(), 1, 100));
	}

	virtual void solve(unsigned int i_case) override
	{
		std::sort(gnus_.begin(), gnus_.end());
		gnus_.erase(std::unique(gnus_.begin(), gnus_.end()), gnus_.end());

		/*********************************************************************
		For each point (= gnu), shift the origin to that point and find
		the maximum number of points that all have the same polar angle.
		**********************************************************************/

		std::vector<Direction> directions;

		std::size_t n_gnus_max = 0;
		for (auto pivot = gnus_.cbegin(); pivot != gnus_.cend(); ++pivot)
		{
			directions.clear();
			for (auto other = gnus_.cbegin(); other != pivot; ++other)
				directions.emplace_back(*other - *pivot);

			std::sort(directions.begin(), directions.end());
			const std::size_t n_points = 1 + max_adjacent_n(directions.cbegin(), directions.cend());
			n_gnus_max = std::max(n_gnus_max, n_points);
		}

		if (n_gnus_max == 1)
			write_ln("Data set #", i_case + 1, " contains a single gnu.");
		else
			write_ln("Data set #", i_case + 1, " contains ", gnus_.size(),
				" gnus, out of which a maximum of ", n_gnus_max, " are aligned.");
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
	std::vector<Point<T>> gnus_;
};

MAIN(CP)

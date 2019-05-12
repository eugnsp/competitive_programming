/*********************************************************************
Watering grass
--------------
UVa ID: 103 82

n sprinklers are installed in a horizontal strip of grass l meters
long and w meters wide. Each sprinkler is installed at the horizontal
center line of the strip. For each sprinkler we are given its position
as the distance from the left end of the center line and its radius
of operation. What is the minimum number of sprinklers to turn on in
order to water the entire strip of grass?

Input
-----
Input consists of a number of cases. The first line for each case
contains integer numbers n, l and w with n <= 10'000. The next n lines
contain two integers giving the position of a sprinkler and its radius
of operation.

Output
------
For each test case output the minimum number of sprinklers needed to
water the entire strip of grass. If it is impossible to water the
entire strip output "-1".

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cmath>
#include <cstddef>
#include <utility>
#include <vector>

using Length = double;
using Interval = std::pair<Length, Length>;

template<class It>
std::size_t n_min_intervals(It first, const It last, const Interval& interval)
{
	if (first == last)
		return 0;

	std::sort(first, last);

	auto right = interval.first;
	std::size_t n = 1;

	while (first != last)
	{
		auto new_right = right;
		while (first != last && first->first <= right)
			new_right = std::max(new_right, first++->second);

		if (new_right == right)
			return 0;
		if (new_right >= interval.second)
			return n;

		right = new_right;
		++n;
	}

	return 0;
}

double sq(double x)
{
	return x * x;
}

struct Sprinkler
{
	Length pos;
	Length radius;
};

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::size_t n_sprinkles;
		if (!read(n_sprinkles))
			return false;

		read(length_, width_);

		sprinklers_.resize(n_sprinkles);
		for (auto& s : sprinklers_)
			read(s.pos, s.radius);

		return true;
	}

	virtual void solve(unsigned int) override
	{
		std::vector<Interval> intervals;
		intervals.reserve(sprinklers_.size());

		for (const auto& s : sprinklers_)
		{
			if (s.radius <= width_ / 2)
				continue;

			const auto dx = std::sqrt(sq(s.radius) - sq(width_) / 4);
			intervals.push_back({s.pos - dx, s.pos + dx});
		}

		const auto n = n_min_intervals(intervals.begin(), intervals.end(), {0., length_});

		if (n != 0)
			write_ln(n);
		else
			write_ln(-1);
	}

private:
	Length width_;
	Length length_;

	std::vector<Sprinkler> sprinklers_;
};

MAIN


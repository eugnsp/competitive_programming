/*********************************************************************
Getting in line
---------------
UVa ID: 002 16

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "util.hpp"
#include "dp_tsp.hpp"
#include <cstddef>
#include <vector>
#include <cmath>
#include <iomanip>

class CP : public CP2
{
private:
	struct Point
	{
		unsigned int x;
		unsigned int y;
	};

private:
	virtual bool read_input() override
	{
		std::size_t n;
		if (!read(n) || n == 0)
			return false;

		assert(between(n, 2, 8));

		points_.resize(n);
		for (auto& p : points_)
			read(p.x, p.y);

		return true;
	}

	virtual void solve(unsigned int i_case) override
	{
		write(std::fixed, std::setprecision(2));
		write_ln("**********************************************************");
		write_ln("Network #", i_case + 1);

		const auto line = shortest_hamiltonian_path(
			points_.size(), [this](std::size_t i, std::size_t j) { return distance(i, j); });

		for (std::size_t j = 0; j < line.second.size() - 1; ++j)
		{
			const auto from = line.second[j];
			const auto to = line.second[j + 1];
			write_ln(
				"Cable requirement to connect (",
				points_[from].x,
				',',
				points_[from].y,
				") to (",
				points_[to].x,
				',',
				points_[to].y,
				") is ",
				distance(from, to),
				" feet.");
		}
		write_ln("Number of feet of cable required is ", line.first, '.');
	}

	double distance(std::size_t i, std::size_t j)
	{
		const auto dx = static_cast<double>(points_[i].x) - points_[j].x;
		const auto dy = static_cast<double>(points_[i].y) - points_[j].y;
		return 16. + std::hypot(dx, dy);
	};

private:
	std::vector<Point> points_;
};



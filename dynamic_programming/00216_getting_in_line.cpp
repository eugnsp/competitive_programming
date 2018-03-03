/*********************************************************************
Getting in line
---------------
UVa ID: 216

Goal:	determine how the computers should be connected
		to minimize the total amount of cable needed.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_tsp.hpp"
#include <cstddef>
#include <vector>
#include <cmath>
#include <iomanip>

class Getting_in_line : public CP2
{
private:
	struct Point
	{
		unsigned int x;
		unsigned int y;
	};

private:
	virtual bool read_input(std::istream& in) override
	{
		// <number of computers = n>
		// <x-coord_1> <y-coord_1>
		// ...
		// <x-coord_n> <y-coord_n>

		std::size_t n;
		
		in >> n;
		if (n == 0)
			return false;

		assert(between(n, 2, 8));

		points_.resize(n);
		for (auto& p : points_)
			in >> p.x >> p.y;

		return true;
	}

	virtual void solve(std::ostream& out, std::size_t i_case) override
	{
		out << std::fixed << std::setprecision(2);
		out << "**********************************************************\n";
		out << "Network #" << i_case + 1 << '\n';

		const auto line = shortest_hamiltonian_path(points_.size(),
			[this](std::size_t i, std::size_t j) { return distance(i, j); });

		for (std::size_t j = 0; j < line.second.size() - 1; ++j)
		{
			const auto from = line.second[j];
			const auto to = line.second[j + 1];
			out << "Cable requirement to connect (" << points_[from].x << ',' << points_[from].y
				<< ") to (" << points_[to].x << ',' << points_[to].y << ") is " << distance(from, to) << " feet.\n";
		}
		out << "Number of feet of cable required is " << line.first << ".\n";
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

int main()
{
	Getting_in_line p;
	return p.run();
}
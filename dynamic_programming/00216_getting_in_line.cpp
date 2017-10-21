// Getting in line
// ---------------
//
// Goal: determine how the computers should be connected into such a chain
// to minimize the total amount of cable needed.
//
// UVa ID: 216
// This file is covered by the LICENSE file in the root of this project.

#include "base.hpp"
#include "dp_tsp.hpp"
#include <cstddef>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

class Getting_in_line : public Program2
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
		// <number of computers>
		// <coord_1_x> <coord_1_y>
		// ...
		// <coord_n_x> <coord_n_y>

		std::size_t n;
		std::cin >> n;

		if (n == 0)
			return false;

		assert(n >= 2 && n <= 8);

		points_.resize(n);
		for (auto& p : points_)
			std::cin >> p.x >> p.y;

		return true;
	}

	virtual void solve(std::size_t i_case) override
	{
		std::cout << std::fixed << std::setprecision(2);
		std::cout << "**********************************************************\n";
		std::cout << "Network #" << i_case + 1 << '\n';

		const auto line = shortest_hamiltonian_path(points_.size(),
			[this](std::size_t i, std::size_t j) { return distance(i, j); });

		for (std::size_t j = 0; j < line.second.size() - 1; ++j)
		{
			const auto from = line.second[j];
			const auto to = line.second[j + 1];
			std::cout << "Cable requirement to connect (" << points_[from].x << ',' << points_[from].y
				<< ") to (" << points_[to].x << ',' << points_[to].y << ") is " << distance(from, to) << " feet.\n";
		}
		std::cout << "Number of feet of cable required is " << line.first << ".\n";
	}

	double distance(std::size_t i, std::size_t j)
	{
		const auto dx = static_cast<double>(points_[i].x) - points_[j].x;
		const auto dy = static_cast<double>(points_[i].y) - points_[j].y;
		return 16 + std::hypot(dx, dy);
	};

private:
	std::vector<Point> points_;
};

int main()
{
	Getting_in_line p;
	return p.run();
}
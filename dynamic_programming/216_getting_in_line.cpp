// Getting in line
// ---------------
//
// Goal: determine how the computers should be connected into such a chain
// to minimize the total amount of cable needed.
//
// UVa ID: 216
// This file is covered by the LICENSE file in the root of this project.

#include "dp_tsp.hpp"
#include <cstddef>
#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>

struct Point
{
	unsigned int x;
	unsigned int y;
};

std::ostream& operator<<(std::ostream& s, const Point& point)
{
	s << '(' << point.x << ',' << point.y << ')';
	return s;
}

// <number of computers>
// <coord_1_x> <coord_1_y>
// ...
// <coord_n_x> <coord_n_y>

int main()
{
	std::cout << std::fixed << std::setprecision(2);

	for (std::size_t i = 1; ; ++i)
	{
		std::size_t n;
		std::cin >> n;

		if (n == 0)
			break;

		assert(n >= 2 && n <= 8);

		std::vector<Point> points(n);
		for (auto& p : points)
			std::cin >> p.x >> p.y;

		std::cout << "**********************************************************\n";
		std::cout << "Network #" << i << '\n';

		const auto distance = [&points](std::size_t i, std::size_t j)
		{
			const auto dx = static_cast<double>(points[i].x) - points[j].x;
			const auto dy = static_cast<double>(points[i].y) - points[j].y;
			return 16 + std::hypot(dx, dy);
		};

		const auto line = shortest_hamiltonian_path(n, distance);
		for (std::size_t j = 0; j < n - 1; ++j)
		{
			const auto from = line.second[j];
			const auto to = line.second[j + 1];
			std::cout << "Cable requirement to connect " << points[from] << " to "
				<< points[to] << " is " << distance(from, to) << " feet.\n";
		}
		std::cout << "Number of feet of cable required is " << line.first << ".\n";
	}

	return 0;
}
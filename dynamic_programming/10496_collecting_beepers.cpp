// Collecting beepers
// ------------------
//
// Goal: find the minimum distance that a 2D robot has to move to get from its
// starting position to each of the beepers and back again to the starting position.
//
// UVa ID: 10496
// This file is covered by the LICENSE file in the root of this project.

#include "dp_tsp.hpp"
#include <cstddef>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

struct Cell
{
	unsigned int x;
	unsigned int y;
};

// <number of test cases>
// <size_x> <size_y>
// <start_x> <start_y>
// <number of beepers>
// <beeper_1_x> <beeper_1_y>
// ...
// <beeper_n_x> <beeper_n_y>

int main()
{
	std::size_t n_tests;
	std::cin >> n_tests;

	while (n_tests--)
	{
		unsigned int size_x, size_y;
		std::cin >> size_x >> size_y;

		Cell start;
		std::cin >> start.x >> start.y;

		std::size_t n;
		std::cin >> n;

		std::vector<Cell> cells(n);
		for (auto& p : cells)
			std::cin >> p.x >> p.y;

		cells.push_back(start);

		const auto shortest_cycle = shortest_hamiltonian_cycle_weight(n + 1,
			[&cells](std::size_t i, std::size_t j)
		{
			const auto& ci = cells[i];
			const auto& cj = cells[j];
			const auto dx = (ci.x > cj.x) ? ci.x - cj.x : cj.x - ci.x;
			const auto dy = (ci.y > cj.y) ? ci.y - cj.y : cj.y - ci.y;
			return dx + dy;
		});

		std::cout << "The shortest path has length " << shortest_cycle << '\n';
	}

	return 0;
}

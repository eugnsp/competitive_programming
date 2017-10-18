// Collecting beepers
// ------------------
//
// Goal: find the minimum distance that a 2D robot has to move to get from its
// starting position to each of the beepers and back again to the starting position
//
// UVa ID: 10496
// This file is covered by the LICENSE file in the root of this project.

#include "matrix.hpp"
#include "bit_mask.hpp"
#include <cstddef>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using T = unsigned int;

struct Cell
{
	T x;
	T y;
};

T min_tsp_distance(const std::vector<Cell>& cells)
{
	assert(!cells.empty());
	assert(cells.size() <= 8 * sizeof(std::size_t));

	const auto distance = [](const Cell& b1, const Cell& b2)
	{
		const auto dx = (b1.x > b2.x) ? b1.x - b2.x : b2.x - b1.x;
		const auto dy = (b1.y > b2.y) ? b1.y - b2.y : b2.y - b1.y;
		return dx + dy;
	};

	const auto n = cells.size();
	if (n == 1)
 		return 0;

	const auto max_mask = static_cast<std::size_t>(1) << (n - 1);
	constexpr auto max_length = static_cast<T>(-1);
	
	// tsp(i, visited_mask) is the minimum length of the path that starts at the cell
	// (cells.back()), visits all the cells in the (visited_mask) and ends at the cell (cells[i])
	Matrix<T> tsp(n, max_mask, max_length);

	// The recurrence relation is:
	// tsp(i, mask) = min {j : mask_j == true} [distance(cells[i], cells[j]) + tsp(j, mask with mask_j = false)]
	// Base case:
	// tsp(i, <0...0>) = distance(cells.back(), cells[i])

	for (std::size_t i = 0; i < n; ++i)
		tsp(i, 0) = distance(cells.back(), cells[i]);

	const auto all_visited_mask = max_mask - 1;
	for (std::size_t visited_mask = 1; visited_mask <= all_visited_mask; ++visited_mask)
		for (std::size_t i = 0; i < n; ++i)
		{
			if (is_bit_set(visited_mask, i))
				continue;

			auto min_length = max_length;
			for (std::size_t j = 0; j < n - 1; ++j)
			{
				if (!is_bit_set(visited_mask, j))
					continue;

				auto mask_with_j_not_visited = visited_mask;
				reset_bit(mask_with_j_not_visited, j);

				assert(tsp(j, mask_with_j_not_visited) != max_length);
				const auto dist = distance(cells[i], cells[j]) + tsp(j, mask_with_j_not_visited);
				min_length = std::min(min_length, dist);
			}

			tsp(i, visited_mask) = min_length;
		}

	return tsp(n - 1, all_visited_mask);
}

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
		T size_x, size_y;
		std::cin >> size_x >> size_y;

		Cell start;
		std::cin >> start.x >> start.y;

		std::size_t n;
		std::cin >> n;

		std::vector<Cell> points(n);
		for (auto& p : points)
			std::cin >> p.x >> p.y;

		points.push_back(start);
		std::cout << "The shortest path has length " << min_tsp_distance(points) << '\n';
	}

	return 0;
}
/*********************************************************************
Collecting beepers
------------------
UVa ID: 104 96

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_tsp.hpp"
#include <cstddef>
#include <vector>
#include <cassert>

class CP : public CP1
{
private:
	struct Cell
	{
		unsigned int x;
		unsigned int y;
	};

private:
	virtual void read_input() override
	{
		unsigned int ignore_size_x, ignore_size_y;
		read(ignore_size_x, ignore_size_y, start.x, start.y);

		std::size_t n;
		read(n);

		assert(n <= 10);

		cells.resize(n);
		for (auto& p : cells)
			read(p.x, p.y);
	}

	virtual void solve(unsigned int) override
	{
		cells.push_back(start);

		const auto shortest_cycle =
			shortest_hamiltonian_cycle_weight(cells.size(), [this](std::size_t i, std::size_t j) {
				const auto& ci = cells[i];
				const auto& cj = cells[j];
				const auto dx = (ci.x > cj.x) ? ci.x - cj.x : cj.x - ci.x;
				const auto dy = (ci.y > cj.y) ? ci.y - cj.y : cj.y - ci.y;
				return dx + dy;
			});

		write_ln("The shortest path has length ", shortest_cycle);
	}

private:
	Cell start;
	std::vector<Cell> cells;
};

MAIN(CP)

/*********************************************************************
Number maze
-----------
UVa ID: 009 29

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include "position.hpp"
#include <array>
#include <cassert>
#include <queue>
#include <utility>
#include <vector>

using Cost = unsigned int;
using Size = unsigned int;
using M = Matrix<Cost, Size>;
using Pos = Position<Size>;

constexpr auto max_cost = static_cast<Cost>(-1);

std::array<Pos, 4> four_neighbours(Pos pos)
{
	constexpr auto m = static_cast<Size>(-1);
	std::array<Pos, 4> neighbours{Pos{0, m}, Pos{1, 0}, Pos{0, 1}, Pos{m, 0}};

	for (auto& neighbour : neighbours)
		neighbour += pos;

	return neighbours;
}

// Returns the minimal cost of the path between corners of the matrix
// using the Dijkstra's algorithm
Cost shortest_path_cost(const M& matrix)
{
	using P = std::pair<Cost, Pos>;
	const Pos top_left{0, 0};
	const Pos bottom_right{matrix.rows() - 1, matrix.cols() - 1};

	if (top_left == bottom_right)
		return matrix(top_left);

	std::priority_queue<P, std::vector<P>, std::greater<P>> queue;
	M costs(matrix.rows(), matrix.cols(), max_cost);

	costs(top_left) = matrix(top_left);
	queue.push({costs(top_left), Pos{top_left}});

	while (!queue.empty())
	{
		const auto [cost, pos] = queue.top();
		queue.pop();

		if (pos == bottom_right)
			return costs(pos);

		if (cost > costs(pos))
			continue;

		for (auto neighbour : four_neighbours(pos))
		{
			if (!is_inside_extents(matrix, neighbour))
				continue;

			const auto neighbour_cost = costs(pos) + matrix(neighbour);
			if (neighbour_cost < costs(neighbour))
			{
				costs(neighbour) = neighbour_cost;
				queue.push({neighbour_cost, neighbour});
			}
		}
	}

	assert(false);
	return max_cost;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		Size rows, cols;
		read(rows, cols);

		maze_.resize(rows, cols);
		read_matrix(maze_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(shortest_path_cost(maze_));
	}

private:
	M maze_;
};

MAIN


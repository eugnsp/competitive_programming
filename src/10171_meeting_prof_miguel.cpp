/*********************************************************************
Meeting Prof. Miguel
--------------------
UVa ID: 101 71

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cassert>
#include <limits>
#include <utility>
#include <vector>

using Size = unsigned char;
using Energy = unsigned int;

constexpr Size n_cities = 26;
constexpr auto infinite_energy = std::numeric_limits<Energy>::max();

using Adjacency_list = std::vector<std::vector<std::pair<Size, Energy>>>;

// Returns a matrix of all-pairs shortest paths using
// the Floyd-Warshall algorithm
Matrix<Energy, Size> all_pairs_shortest_paths(const Adjacency_list& graph)
{
	assert(graph.size() == n_cities);
	Matrix<Energy, Size> dist(n_cities, n_cities, infinite_energy);

	for (Size vertex = 0; vertex < n_cities; ++vertex)
	{
		dist(vertex, vertex) = 0;
		for (auto succ : graph[vertex])
			// If there are multiple edges, use the smallest weight
			dist(vertex, succ.first) = std::min(dist(vertex, succ.first), succ.second);
	}

	for (Size k = 0; k < n_cities; ++k)
		for (Size i = 0; i < n_cities; ++i)
			for (Size j = 0; j < n_cities; ++j)
				if (dist(i, k) != infinite_energy && dist(k, j) != infinite_energy)
					dist(i, j) = std::min(dist(i, j), dist(i, k) + dist(k, j));

	return dist;
}

std::pair<Energy, std::vector<Size>> meet_places(const Adjacency_list& roads_y,
	const Adjacency_list& roads_m, Size source_y, Size source_m)
{
	auto en_y = all_pairs_shortest_paths(roads_y);
	auto en_m = all_pairs_shortest_paths(roads_m);

	Energy min_energy = infinite_energy;
	std::vector<Size> meet_places;

	for (Size meet = 0; meet < n_cities; ++meet)
	{
		const auto ey = en_y(source_y, meet);
		const auto em = en_m(source_m, meet);
		if (ey != infinite_energy && em != infinite_energy)
			min_energy = std::min(min_energy, ey + em);
	}

	if (min_energy != infinite_energy)
		for (Size meet = 0; meet < n_cities; ++meet)
		{
			const auto ey = en_y(source_y, meet);
			const auto em = en_m(source_m, meet);
			if (ey != infinite_energy && em != infinite_energy && ey + em == min_energy)
				meet_places.push_back(meet);
		}

	return {min_energy, meet_places};
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::size_t n_streets;
		if (!read(n_streets) || n_streets == 0)
			return false;

		roads_y_.clear();
		roads_m_.clear();
		roads_y_.resize(n_cities);
		roads_m_.resize(n_cities);

		for (std::size_t s = 0; s < n_streets; ++s)
		{
			char type, dir, from, to;
			Energy energy;
			read(type, dir, from, to, energy);
			assert(type == 'Y' || type == 'M');
			assert(dir == 'U' || dir == 'B');
			assert(from >= 'A' && from <= 'Z' && to >= 'A' && to <= 'Z');
			assert(energy < 500);

			from -= 'A';
			to -= 'A';

			auto& roads = (type == 'Y') ? roads_y_ : roads_m_;
			roads[from].push_back({to, energy});
			if (dir == 'B')
				roads[to].push_back({from, energy});
		}

		read(source_y_, source_m_);
		source_y_ -= 'A';
		source_m_ -= 'A';

		return true;
	}

	virtual void solve(unsigned int) override
	{
		auto places = meet_places(roads_y_, roads_m_, source_y_, source_m_);
		if (!places.second.empty())
		{
			write(places.first, ' ');
			write_vec(places.second, [](Size m) { return static_cast<char>('A' + m); });
		}
		else
			write("You will never meet.");
		write_ln();
	}

private:
	Adjacency_list roads_y_, roads_m_;
	char source_y_, source_m_;
};

MAIN(CP)

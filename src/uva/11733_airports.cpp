/*********************************************************************
Airports
--------
UVa ID: 117 22

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>
#include <utility>

using Size = unsigned int;
using Cost = unsigned int;

class Disjoint_set
{
public:
	// Creates a disjoint set of (n) disjoint elements
	Disjoint_set(Size n)
	{
		ranks_.assign(n, 0);
		parents_.resize(n);
		std::iota(parents_.begin(), parents_.end(), static_cast<Size>(0));
	}

	void unite(Size x, Size y)
	{
		const auto px = find_parent(x);
		const auto py = find_parent(y);
		assert(px != py);

		if (ranks_[px] > ranks_[py])
			parents_[py] = px;
		else
		{
			parents_[px] = py;
			if (ranks_[px] == ranks_[py])
				++ranks_[py];
		}
	}

	bool is_same_set(Size x, Size y) const
	{
		return find_parent(x) == find_parent(y);
	}

private:
	Size find_parent(Size vertex) const
	{
		auto& parent = parents_[vertex];
		if (parent != vertex)
			parent = find_parent(parent);

		return parent;
	}

private:
	std::vector<Size> ranks_;
	mutable std::vector<Size> parents_;
};

struct Road
{
	Size loc1;
	Size loc2;
	Cost cost;

	bool operator<(const Road& other) const
	{
		return cost < other.cost;
	}
};

std::pair<Cost, Size> total_cost_and_n_airports(
	Size n_locations, Cost airport_cost, const std::vector<Road>& roads)
{
	const auto is_cheap_road = [airport_cost](const Road& road) {
		return road.cost < airport_cost;
	};

	std::vector<Road> cheap_roads(std::count_if(roads.begin(), roads.end(), is_cheap_road));
	std::copy_if(roads.begin(), roads.end(), cheap_roads.begin(), is_cheap_road);
	std::sort(cheap_roads.begin(), cheap_roads.end());

	// No roads at the beginning
	auto n_airports = n_locations;
	Cost n_total_cost = 0;

	Disjoint_set ds(n_locations);

	for (const auto& road : cheap_roads)
	{
		// Building a road
		if (!ds.is_same_set(road.loc1, road.loc2))
		{
			ds.unite(road.loc1, road.loc2);
			n_total_cost += road.cost;
			--n_airports;
		}

		if (n_airports == 1)
			break;
	}

	n_total_cost += static_cast<Cost>(n_airports * airport_cost);
	return {n_total_cost, n_airports};
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		Size n_roads;

		read(n_locations_, n_roads, airport_cost_);
		assert(0 < n_locations_ && n_locations_ <= 10'000);
		assert(n_roads <= 100'000);
		assert(0 < airport_cost_ && airport_cost_ <= 10'000);

		roads_.clear();
		roads_.reserve(n_roads);
		for (std::size_t i = 0; i < n_roads; ++i)
		{
			Road road;
			read(road.loc1, road.loc2, road.cost);
			--road.loc1; // To zero-based indexing
			--road.loc2;
			roads_.push_back(road);
		}
	}

	virtual void solve(unsigned int i_case) override
	{
		const auto a = total_cost_and_n_airports(n_locations_, airport_cost_, roads_);
		write_ln("Case #", i_case + 1, ": ", a.first, ' ', a.second);
	}

private:
	Size n_locations_;
	Cost airport_cost_;
	std::vector<Road> roads_;
};



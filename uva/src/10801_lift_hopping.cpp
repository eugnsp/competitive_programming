/*********************************************************************
Lift hopping
------------
UVa ID: 108 01

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

using Time = unsigned int;
using Size = unsigned int;

constexpr auto max_time = std::numeric_limits<Time>::max();

struct Elevator
{
	Time secs_per_floor;
	std::vector<Size> floors;
};

struct P
{
	Time time;
	Size elevator;
	Size floor_index;
};

// Strict weak ordering
struct P_cmp
{
	bool operator()(const P& p1, const P& p2) const
	{
		return p1.time > p2.time;
	}
};

using Queue = std::priority_queue<P, std::vector<P>, P_cmp>;
using Times = std::vector<std::vector<Time>>;

Size binary_find(const std::vector<Size>& vec, Size value)
{
	const auto p = std::lower_bound(vec.begin(), vec.end(), value);
	if (p != vec.end() && *p == value)
		return static_cast<Size>(p - vec.begin());
	else
		return static_cast<Size>(vec.size());
}

Size find_first_elevator(const std::vector<Elevator>& elevators, Size start_floor)
{
	auto first =
		std::find_if(elevators.begin(), elevators.end(), [start_floor](const Elevator& el) {
			return el.floors.front() == start_floor;
		});

	if (first != elevators.end())
		return static_cast<Size>(first - elevators.begin());
	else
		return static_cast<Size>(elevators.size());
}

void relex_and_enqueue(Queue& queue, Times& times, Time time, Size elevator, Size floor_index)
{
	auto& curr_time = times[elevator][floor_index];
	if (time < curr_time)
	{
		curr_time = time;
		queue.push({time, elevator, floor_index});
	}
}

Time minimal_time(Size dest_floor, const std::vector<Elevator>& elevators)
{
	const Size start_floor = 0;
	if (dest_floor == start_floor)
		return 0;

	const auto n_elevators = static_cast<Size>(elevators.size());
	auto first_elevator = find_first_elevator(elevators, start_floor);
	if (first_elevator == n_elevators)
		return max_time;

	Queue queue;
	Times times(n_elevators);
	for (Size el = 0; el < n_elevators; ++el)
		times[el].assign(elevators[el].floors.size(), max_time);

	times[first_elevator][0] = 0;
	queue.push({0, first_elevator, 0});

	while (!queue.empty())
	{
		const auto p = queue.top();
		queue.pop();

		const auto el = p.elevator;
		auto& elevator = elevators[el];

		const auto floor_index = p.floor_index;
		const auto floor = elevator.floors[floor_index];
		const auto time = times[el][floor_index];

		if (p.time > time)
			continue;

		// Go up/down using the same elevator
		for (auto d : {-1, 1})
		{
			const auto next_floor_index = floor_index + d;
			if (next_floor_index < elevator.floors.size())
			{
				const auto next_floor = elevator.floors[next_floor_index];
				const auto next_time = time + elevator.secs_per_floor * abs_diff(floor, next_floor);
				relex_and_enqueue(queue, times, next_time, el, next_floor_index);
			}
		}

		// Change the elevator
		for (Size next_el = 0; next_el < n_elevators; ++next_el)
			if (next_el != el)
			{
				auto& floors = elevators[next_el].floors;
				const auto next_floor_index = binary_find(floors, floor);
				if (next_floor_index == floors.size())
					continue;

				const auto next_time = time + (floor == 0 ? 0 : 60);
				relex_and_enqueue(queue, times, next_time, next_el, next_floor_index);
			}
	}

	Time min_time = max_time;
	for (Size el = 0; el < n_elevators; ++el)
	{
		auto& floors = elevators[el].floors;
		const auto floor_index = binary_find(floors, dest_floor);
		if (floor_index != floors.size())
			min_time = std::min(min_time, times[el][floor_index]);
	}

	return min_time;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		Size n_elevators;
		if (!read(n_elevators))
			return false;

		read(dest_floor_);

		assert(1 <= n_elevators && n_elevators <= 5);
		elevators_.resize(n_elevators);

		std::vector<Time> speeds;
		read_vec(n_elevators, speeds);
		ignore_line();

		for (Size el = 0; el < n_elevators; ++el)
		{
			elevators_[el].secs_per_floor = speeds[el];

			std::vector<Size> floors;
			read_vec_ln(floors);

			assert(std::is_sorted(floors.begin(), floors.end()));
			elevators_[el].floors = std::move(floors);
		}

		return true;
	}

	virtual void solve(unsigned int) override
	{
		const auto time = minimal_time(dest_floor_, elevators_);
		if (time != max_time)
			write_ln(time);
		else
			write_ln("IMPOSSIBLE");
	}

private:
	Size dest_floor_;
	std::vector<Elevator> elevators_;
};



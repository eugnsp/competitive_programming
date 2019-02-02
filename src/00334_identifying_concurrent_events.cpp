/*********************************************************************
Identifying concurrent events
-----------------------------
UVa ID: 003 34

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cassert>
#include <cstddef>
#include <limits>
#include <map>
#include <string>
#include <utility>
#include <vector>

using Adjacency_list = std::vector<std::vector<std::size_t>>;

class Event_map
{
public:
	void clear()
	{
		map_.clear();
		map_back_.clear();
	}

	std::size_t index(std::string name)
	{
		const auto pos = map_.find(name);
		if (pos != map_.end())
			return pos->second;

		const auto index = map_.size();
		map_.insert({name, index});
		map_back_.push_back(name);
		return index;
	}

	std::size_t index(std::string name) const
	{
		return map_.at(name);
	}

	std::string name(std::size_t index) const
	{
		return map_back_[index];
	}

private:
	std::map<std::string, std::size_t> map_;
	std::vector<std::string> map_back_;
};

void adjust_graph_size(Adjacency_list& graph, std::size_t vertex_index)
{
	if (vertex_index >= graph.size())
		graph.resize(vertex_index + 1);
}

// Returns a transitive closure of a graph using
// the Floyd-Warshall algorithm
Matrix<bool> transitive_closure(const Adjacency_list& graph)
{
	const auto n_vertices = graph.size();
	Matrix<bool> dist(n_vertices, n_vertices, false);

	for (std::size_t vertex = 0; vertex < n_vertices; ++vertex)
	{
		dist(vertex, vertex) = true;
		for (auto succ : graph[vertex])
			dist(vertex, succ) = true;
	}

	for (std::size_t k = 0; k < n_vertices; ++k)
		for (std::size_t i = 0; i < n_vertices; ++i)
			for (std::size_t j = 0; j < n_vertices; ++j)
				dist(i, j) = dist(i, j) || (dist(i, k) && dist(k, j));

	return dist;
}

std::pair<std::size_t, std::vector<std::pair<std::size_t, std::size_t>>> concurrent_events(
	const Adjacency_list& event_graph)
{
	const auto tt = transitive_closure(event_graph);

	std::size_t n_concurrent_events = 0;
	std::vector<std::pair<std::size_t, std::size_t>> events;

	for (std::size_t i = 0; i < event_graph.size(); ++i)
		for (std::size_t j = 0; j < i; ++j)
			if (!tt(i, j) && !tt(j, i))
			{
				++n_concurrent_events;
				if (events.size() < 2)
					events.push_back({i, j});
			}

	return {n_concurrent_events, events};
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::size_t n_computations;
		if (!read(n_computations) || n_computations == 0)
			return false;

		map_.clear();
		graph_.clear();
		for (std::size_t i = 0; i < n_computations; ++i)
		{
			std::size_t n_events;
			std::string prev_event;
			read(n_events, prev_event);

			auto prev_index = map_.index(prev_event);
			adjust_graph_size(graph_, prev_index);

			for (std::size_t ev = 1; ev < n_events; ++ev)
			{
				std::string event;
				read(event);

				auto index = map_.index(event);
				adjust_graph_size(graph_, index);
				graph_[prev_index].push_back(index);

				prev_index = index;
			}
		}

		std::size_t n_messages;
		read(n_messages);

		for (std::size_t m = 0; m < n_messages; ++m)
		{
			std::string sender, receiver;
			read(sender, receiver);
			graph_[map_.index(sender)].push_back(map_.index(receiver));
		}

		return true;
	}

	virtual void solve(unsigned int i_case) override
	{
		const auto events = concurrent_events(graph_);

		write("Case ", i_case + 1, ", ");
		if (events.first > 0)
		{
			write_ln(events.first, " concurrent events:");
			for (auto& evs : events.second)
				write('(', map_.name(evs.first), ',', map_.name(evs.second), ") ");
		}
		else
			write("no concurrent events.");
		write_ln();
	}

private:
	Event_map map_;
	Adjacency_list graph_;
};

MAIN(CP)

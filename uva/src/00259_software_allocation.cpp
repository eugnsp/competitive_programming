/*********************************************************************
Software allocation
-------------------
UVa ID: 002 59

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <optional>
#include <queue>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using T = unsigned int;
constexpr auto unvisited_vertex = static_cast<T>(-1);

struct Job
{
	T app;
	T n_users;
	std::vector<T> comps;
};

template<T n_vertices>
class Graph
{
public:
	struct Edge
	{
		T to;
		T flow;
	};

public:
	const std::vector<T>& edges(T vertex) const
	{
		assert(vertex < n_vertices);
		return edge_indices_[vertex];
	}

	Edge& edge(T index)
	{
		return edges_[index];
	}

	Edge& opposite_edge(T index)
	{
		const auto opposite_index = index ^ 1;
		return edges_[opposite_index];
	}

	void add_edge(T from, T to, T flow)
	{
		const auto edge_index = static_cast<T>(edges_.size());

		edges_.push_back({to, flow});
		edge_indices_[from].push_back(edge_index);

		edges_.push_back({from, 0});
		edge_indices_[to].push_back(edge_index + 1);
	}

private:
	// Indices of the outgoing edges in the (edges) array
	std::array<std::vector<T>, n_vertices> edge_indices_;

	// An edge and its opposite edge are stored as consecutive pairs,
	// i.e. the opposite edge index is given by (edge_index ^ 1)
	std::vector<Edge> edges_;
};

class Software_allocation
{
private:
	static constexpr T n_max_apps = 26;
	static constexpr T n_comps = 10;

	static constexpr T source_vertex_index = 0;
	static constexpr T sink_vertex_index = 1 + n_max_apps + n_comps;
	static constexpr T n_vertices = sink_vertex_index + 1;

	using G = Graph<n_vertices>;

public:
	Software_allocation(const std::vector<Job>& jobs) : jobs_(jobs)
	{}

	std::optional<std::array<T, n_comps>> get() const
	{
		auto graph = make_resudial_graph();

		T max_flow = 0;
		while (bfs_augmenting_path(graph))
			++max_flow;

		if (max_flow == n_apps())
		{
			std::array<T, n_comps> allocation;
			std::fill(allocation.begin(), allocation.end(), unvisited_vertex);

			for (auto& job : jobs_)
				for (auto edge_index : graph.edges(app_vertex_index(job.app)))
					if (graph.opposite_edge(edge_index).flow == 1)
					{
						const auto computer = comp_by_vertex_index(graph.edge(edge_index).to);
						allocation[computer] = job.app;
					}

			return allocation;
		}
		else
			return {};
	}

private:
	static T app_vertex_index(T app)
	{
		assert(app < n_max_apps);
		return app + 1;
	}

	static T comp_vertex_index(T computer)
	{
		assert(computer < n_comps);
		return computer + 1 + n_max_apps;
	}

	static T comp_by_vertex_index(T vertex)
	{
		assert(vertex >= comp_vertex_index(0) && vertex <= comp_vertex_index(9));
		return vertex - (1 + n_max_apps);
	}

	G make_resudial_graph() const
	{
		G graph;

		for (auto& job : jobs_)
		{
			const auto app_vertex = app_vertex_index(job.app);
			graph.add_edge(source_vertex_index, app_vertex, job.n_users);
			for (auto comp : job.comps)
				graph.add_edge(app_vertex, comp_vertex_index(comp), 1);
		}

		for (T comp = 0; comp < n_comps; ++comp)
			graph.add_edge(comp_vertex_index(comp), sink_vertex_index, 1);

		return graph;
	}

	T n_apps() const
	{
		T n = 0;
		for (auto& j : jobs_)
			n += j.n_users;
		return n;
	}

	static bool bfs_augmenting_path(G& graph)
	{
		// After search, (pred[vertex]) contains a pair of the previous vertex and edge indices,
		// this array is also used to skip visited vertices
		std::array<std::pair<T, T>, n_vertices> pred;
		std::fill(pred.begin(), pred.end(), std::make_pair(unvisited_vertex, 0));

		std::queue<T> queue;
		queue.push(+source_vertex_index); // Make rvalue

		while (!queue.empty())
		{
			const auto v = queue.front();
			queue.pop();

			if (v == sink_vertex_index)
				break;

			for (auto edge_index : graph.edges(v))
			{
				auto& edge = graph.edge(edge_index);
				if (edge.flow > 0 && pred[edge.to].first == unvisited_vertex)
				{
					pred[edge.to] = {v, edge_index};
					queue.push(edge.to);
				}
			}
		}

		if (pred[sink_vertex_index].first == unvisited_vertex)
			return false;

		// Recover the path and update flows
		auto dest = sink_vertex_index;
		while (true)
		{
			--graph.edge(pred[dest].second).flow;
			++graph.opposite_edge(pred[dest].second).flow;

			if (pred[dest].first == source_vertex_index)
				break;
			else
				dest = pred[dest].first;
		}

		return true;
	}

private:
	const std::vector<Job>& jobs_;
};

T read_byte(std::istringstream& in, char offset)
{
	char c;
	in >> c;
	c -= offset;
	return static_cast<T>(c);
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		jobs_.clear();

		std::string str;
		while (read_ln_non_empty(str))
		{
			std::istringstream s(str);

			Job job;
			job.app = read_byte(s, 'A');
			job.n_users = read_byte(s, '0');

			s.ignore();
			while (true)
			{
				const auto computer = read_byte(s, '0');
				if (computer > 9)
					break;
				else
					job.comps.push_back(computer);
			}

			jobs_.push_back(std::move(job));
		}

		return !jobs_.empty();
	}

	virtual void solve(unsigned int) override
	{
		Software_allocation sa(jobs_);

		const auto allocation = sa.get();
		if (allocation)
			for (const auto a : *allocation)
				write(a == unvisited_vertex ? '_' : static_cast<char>(a + 'A'));
		else
			write('!');

		write_ln();
	}

private:
	std::vector<Job> jobs_;
};

MAIN


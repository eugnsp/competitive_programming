/*********************************************************************
Dominator
---------
UVa ID: 119 02

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cassert>
#include <cstddef>
#include <string>
#include <vector>

using Graph = Matrix<bool>;

class Dominator
{
public:
	Dominator(const Graph& adj_matrix)
	{
		assert(adj_matrix.rows() == adj_matrix.cols());

		const auto n = adj_matrix.rows();
		adj_list_.resize(n);
		for (std::size_t to = 0; to < n; ++to)
			for (std::size_t from = 0; from < n; ++from)
				if (adj_matrix(from, to))
					adj_list_[from].push_back(to);

		do_depth_first_search([this](std::size_t vertex) {
			reachable_.push_back(vertex);
			return false; // Do not stop
		});
	}

	// Returns the vertices that are dominated by the vertex (va)
	std::vector<bool> dominatable(std::size_t vertex) const
	{
		std::vector<bool> dominatable(adj_list_.size(), false);
		for (auto v : reachable_)
			dominatable[v] = true;

		do_depth_first_search([&dominatable, vertex](std::size_t v) {
			dominatable[v] = (vertex == v);
			return vertex == v; // Stop if (vertex) has been reached
		});

		return dominatable;
	}

private:
	template<class Func>
	void do_depth_first_search(Func func) const
	{
		static std::vector<bool> visited;

		visited.assign(adj_list_.size(), false);
		depth_first_search(visited, 0, func);
	}

	// Performs the depth-first-search that starts at the (vertex) and calls
	// the (func) for each visited vertex; if (func) returns true, aborts the search
	template<class Func>
	void depth_first_search(std::vector<bool>& visited, std::size_t vertex, Func func) const
	{
		visited[vertex] = true;
		const bool abort = func(vertex);
		if (abort)
			return;

		for (auto next : adj_list_[vertex])
			if (!visited[next])
				depth_first_search(visited, next, func);
	}

private:
	std::vector<std::vector<std::size_t>> adj_list_;
	std::vector<std::size_t> reachable_;
};

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		unsigned int n;
		read(n);
		assert(0 < n && n <= 100);

		adj_matrix_.resize(n, n);
		read_matrix<unsigned int>(adj_matrix_, [](unsigned int x) { return x > 0; });
	}

	virtual void solve(unsigned int i_case) override
	{
		write_ln("Case ", i_case, ':');

		const Dominator d(adj_matrix_);
		const auto n = adj_matrix_.rows();

		const auto dashes = std::string(2 * n - 1, '-');
		write_ln('+', dashes, '+');
		for (std::size_t vertex = 0; vertex < n; ++vertex)
		{
			write('|');
			for (auto fd : d.dominatable(vertex))
				write(fd ? 'Y' : 'N', '|');
			write_ln();
			write_ln('+', dashes, '+');
		}
	}

private:
	Graph adj_matrix_;
};

MAIN

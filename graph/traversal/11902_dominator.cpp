/*********************************************************************
Dominator
---------
UVa ID: 119 02

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cassert>
#include <string>
#include <vector>

using Size = unsigned int;
using Graph = Matrix<bool, Size>;

class Dominator
{
public:
	Dominator(const Graph& adj_matrix)
	{
		assert(adj_matrix.rows() == adj_matrix.cols());

		const auto n = adj_matrix.rows();
		adj_list_.resize(n);
		for (Size to = 0; to < n; ++to)
			for (Size from = 0; from < n; ++from)
				if (adj_matrix(from, to))
					adj_list_[from].push_back(to);

		do_depth_first_search([this](Size vertex)
			{
				reachable_.push_back(vertex);
				return false;			// Do not stop
			});
	}

	// Returns the vertices that are dominated by the vertex (va)
	std::vector<bool> dominatable(Size vertex) const
	{
		std::vector<bool> dominatable(adj_list_.size(), false);
		for (auto v : reachable_)
			dominatable[v] = true;

		do_depth_first_search([&dominatable, vertex](Size v)
			{
				dominatable[v] = (vertex == v);
				return vertex == v;		// Stop if (vertex) has been reached
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
	void depth_first_search(std::vector<bool>& visited, Size vertex, Func func) const
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
	std::vector<std::vector<Size>> adj_list_;
	std::vector<Size> reachable_;
};

class CP : public CP1
{
private:
	virtual void read_input(std::istream& in) override
	{
		unsigned int n;
		in >> n;
		assert(0 < n && n <= 100);

		adj_matrix_.resize(n, n);
		read_matrix<unsigned int>(in, adj_matrix_);
	}

	virtual void solve(std::ostream& out, unsigned int i_case) const override
	{
		out << "Case " << i_case + 1 << ":\n";

		const Dominator d(adj_matrix_);
		const auto n = adj_matrix_.rows();

		const auto dashes = std::string(2 * n - 1, '-');
		out << '+' << dashes << "+\n";
		for (Size vertex = 0; vertex < n; ++vertex)
		{
			out << '|';
			for (auto fd : d.dominatable(vertex))
				out << (fd ? 'Y' : 'N') << '|';
			out << "\n+" << dashes << "+\n";
		}
	}

private:
	Graph adj_matrix_;
};

int main()
{
	CP p;
	return p.run();
}

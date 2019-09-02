/*********************************************************************
Randomly wired neural nets
--------------------------
UVa ID: 005 82

Graphs are powerful tools for modeling connected entities of all kinds
(including randomly wired neural nets). In this problem, we wish to
prune unnecessary nodes from a graph that is modeling a particular
kind of neural net. In particular, we wish to remove neurons from the
neural net that don't have any potential across them when we introduce
a potential across two given nodes of the network. Let G = (V, E)
be an undirected graph. For two given distinct vertices v and w of G,
a path P(v, w) in G between v and w is called simple if no vertex
of G appears in it more than once. It is straightforward to show
that a neuron in a neural net will support flow if and only if the
corresponding edge in the graph model of the neural net lies on some
simple path between v and w. Thus, the set of all vertices of G that
are on at least one simple path between v and w represent the vertices
that would be present in a model of the neural net with the unnecessary
neurons removed. Your program is to print out a modified graph G such
that each vertex in the graph is present on at least one simple path
between v and w.

Input
-----
The input will consist of a graph G described as an adjacency list and
two distinguished vertices, v and w. The first line of the input will
contain two numbers separated by a space, indicating the distinguished
vertices, v and w. The second line will contain one number n,
specifying the number of vertices in G. The next n lines specify the
adjacency list for the graph, one line for each vertex, ordered from
vertex_0 to vertex_{n - 1}. The line corresponding to vertex q (i.e.,
the q-th line in the adjacency list portion of the input file) consists
of an integer k specifying the degree of q, followed by k integers
specifying the vertices connected to vertex q. All of the numbers
in one line will be separated by a single space. The maximum number
of vertices is 1024.

Output
------
The output of the program will consist of an ordered list of all
vertices of G such that each of the identified vertices is on some
simple path in G between v and w. Lines 0 through n - 1, respectively.
If a given vertex is not present in the modified graph, an "X" should
be printed on that line. Otherwise, the vertices (in the modified
graph) to which the given vertex is connected should be printed.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

using Adjacency_list = std::vector<std::size_t>;
using Graph = std::vector<Adjacency_list>;

// Returns the array of boolean flags for all graph vertices which specify
// whether a vertex belongs to the same biconnected component as the one
// that contains the edge (src_ - dst_); if the original graph doesn't
// contain this edge, it is implicitly added to the set of its edges
class All_simple_paths
{
public:
	All_simple_paths(const Graph& graph, const std::size_t src, const std::size_t dst) :
		graph_(graph), src_(src), dst_(dst)
	{}

	std::vector<bool> operator()()
	{
		info_dfs();
		return bicomp_dfs();
	}

private:
	static constexpr std::size_t unvisited_id = 0;

	struct Info
	{
		std::size_t id = unvisited_id; // Sequential ID in the DFS traversal
		std::size_t low_link;		   // The lowest ID that can be reached via
									   // tree edges and at most one back-edge
	};

	void info_dfs(const std::size_t src, const std::size_t parent)
	{
		infos_[src].id = infos_[src].low_link = ++dfs_id_;

		for (const auto dst : graph_[src])
			if (infos_[dst].id == unvisited_id) // Tree edge
			{
				info_dfs(dst, src);
				infos_[src].low_link = std::min(infos_[src].low_link, infos_[dst].low_link);
			}
			else if (dst != parent) // Back edge
				infos_[src].low_link = std::min(infos_[src].low_link, infos_[dst].id);
	}

	void info_dfs()
	{
		dfs_id_ = unvisited_id;
		infos_.assign(graph_.size(), Info{});

		infos_[src_].id = infos_[src_].low_link = ++dfs_id_;
		infos_[dst_].low_link = infos_[src_].id;

		info_dfs(dst_, src_);
	}

	void bicomp_dfs(std::size_t src, std::vector<bool>& visited)
	{
		visited[src] = true;
		for (const auto dst : graph_[src])
			if (!visited[dst])
			{
				if (infos_[dst].low_link < infos_[src].id)
					bicomp_dfs(dst, visited);
			}
	}

	std::vector<bool> bicomp_dfs()
	{
		std::vector<bool> visited(graph_.size(), false);
		visited[src_] = true;

		bicomp_dfs(dst_, visited);
		return visited;
	}

private:
	const Graph& graph_;
	const std::size_t src_;
	const std::size_t dst_;

	std::size_t dfs_id_;
	std::vector<Info> infos_;
};

class CP : public CP3
{
private:
	virtual void read_input() override
	{
		read(src_, dst_);

		std::size_t n_vertices;
		read(n_vertices);

		assert(src_ < n_vertices);
		assert(dst_ < n_vertices);

		graph_.resize(n_vertices);
		for (auto& list : graph_)
			read_size_vec(list);
	}

	virtual void solve() override
	{
		const auto flags = All_simple_paths{graph_, src_, dst_}();
		for (std::size_t i = 0; i < graph_.size(); ++i)
			if (flags[i])
			{
				bool first = true;
				for (auto vertex : graph_[i])
					if (flags[vertex])
					{
						if (!std::exchange(first, false))
							write(' ');
						write(vertex);
					}
				write_ln();
			}
			else
				write_ln('X');
	}

private:
	std::size_t src_, dst_;
	Graph graph_;
};

MAIN


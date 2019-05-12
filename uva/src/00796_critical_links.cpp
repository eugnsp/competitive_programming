/*********************************************************************
Critical links
--------------
UVa ID: 007 96

In a computer network a link L, which interconnects two servers, is
considered critical if there are at least two servers A and B such
that all network interconnection paths between A and B pass through L.
Removing a critical link generates two disjoint subnetworks such that
any two servers of a subnetworkare interconnected. It is known that:
	1. the connection links are bidirectional;
	2. a server is not directly connected to itself;
	3. two servers are interconnected if they are directly connected
   	   or if they are interconnected with the same server;
	4. the network can have standalone subnetworks.
Write a program that finds all critical links of a given computer
network.

Input
-----
The program reads sets of data from a text file. The first line
contains a positive integer no_of_servers (possibly 0) which is the
number of network servers. The next no_of_servers_lines, one for each
server in the network, are randomly ordered and show the way servers are
connected. The line corresponding to server k, 0 <= k < no_of_servers,
specifies the number of direct connections of server k and the servers
which are directly connected to server k. Servers are represented
by integers from 0 to no_of_servers - 1. Input data are correct.

Output
------
The result of the program is on standard output. For each data set the
program prints the number of critical links and the critical links, one
link per line, starting from the beginning of the line. The links are
listed in ascending order according to their first element. The output
for the data set is followed by an empty line.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

using Adjacency_list = std::vector<std::size_t>;
using Graph = std::vector<Adjacency_list>;

class Bridges
{
private:
	using Edge = std::pair<std::size_t, std::size_t>;

public:
	Bridges(const Graph& graph) : graph_(graph)
	{}

	std::vector<Edge> operator()() const
	{
		std::vector<Edge> bridges;

		dfs_id_ = unvisited_id;
		infos_.assign(graph_.size(), Info{});

		constexpr auto nonexistent_vertex = static_cast<std::size_t>(-1);
		for (std::size_t src = 0; src < graph_.size(); ++src)
			if (infos_[src].id == unvisited_id)
				bridges_dfs(src, nonexistent_vertex, bridges);

		return bridges;
	}

private:
	static constexpr std::size_t unvisited_id = 0;

	struct Info
	{
		std::size_t id = unvisited_id; // Sequential ID in the DFS traversal
		std::size_t low_link;		   // The lowest ID that can be reached via
									   // tree edges and at most one back-edge
	};

	void bridges_dfs(const std::size_t src, const std::size_t parent, std::vector<Edge>& bridges) const
	{
		infos_[src].id = infos_[src].low_link = ++dfs_id_;

		for (const auto dst : graph_[src])
			if (infos_[dst].id == unvisited_id) // Tree edge
			{
				bridges_dfs(dst, src, bridges);
				infos_[src].low_link = std::min(infos_[src].low_link, infos_[dst].low_link);
				if (infos_[src].id < infos_[dst].low_link)
				{
					if (src < dst)
						bridges.emplace_back(src, dst);
					else
						bridges.emplace_back(dst, src);
				}
			}
			else if (dst != parent) // Back edge
				infos_[src].low_link = std::min(infos_[src].low_link, infos_[dst].id);
	}

private:
	const Graph& graph_;

	mutable std::size_t dfs_id_;
	mutable std::vector<Info> infos_;
};

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::size_t n_servers;
		if (!read(n_servers))
			return false;

		network_.assign(n_servers, {});
		for (std::size_t i = 0; i < n_servers; ++i)
		{
			std::size_t server_id;
			read(server_id);

			char ch1, ch2;
			std::size_t n_loc_servers;
			read(ch1, n_loc_servers, ch2);
			assert(ch1 == '(' && ch2 == ')');
			network_[server_id].resize(n_loc_servers);
			for (auto& server : network_[server_id])
				read(server);
		}

		return true;
	}

	virtual void solve(unsigned int) override
	{
		auto bridges = Bridges{network_}();
		std::sort(bridges.begin(), bridges.end());

		write_ln(bridges.size(), " critical links");
		for (const auto& b : bridges)
			write_ln(b.first, " - ", b.second);

		write_ln();
	}

private:
	Graph network_;
};

MAIN


/*********************************************************************
Beverages
---------
UVa ID: 110 60

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "io.hpp"
#include <algorithm>
#include <cassert>
#include <string>
#include <queue>
#include <vector>

using Size = unsigned int;
using Vertex_list = std::vector<Size>;
using Adjacency_list = std::vector<Vertex_list>;

// Returns the list of topologically sorted vertices in the (graph)
// (the Kahn's algorithm is used)
auto topologic_sort(const Adjacency_list& graph)
{
	Vertex_list sorted_vertices;
	
	std::vector<Size> in_degrees(graph.size(), 0);
	for (auto& vertex : graph)
		for (auto succ : vertex)
			++in_degrees[succ];

	std::priority_queue<Size, Vertex_list, std::greater<>> zero_in_degree_queue;
	for (Size i = 0; i < graph.size(); ++i)
		if (in_degrees[i] == 0)
			zero_in_degree_queue.push(i);

	while (!zero_in_degree_queue.empty())
	{
		const auto v = zero_in_degree_queue.top();
		zero_in_degree_queue.pop();

		sorted_vertices.push_back(v);
		for (auto succ : graph[v])
			if (in_degrees[succ] > 0 && --in_degrees[succ] == 0)
				zero_in_degree_queue.push(succ);
	}

	return sorted_vertices;
}

class CP : public CP2
{
private:
	virtual bool read_input(std::istream& in) override
	{
		Size n_beverages;
		if (!(in >> n_beverages))
			return false;

		assert(1 <= n_beverages && n_beverages <= 100);
		read_vector(in, n_beverages, beverages_);

		Size n_precedences;
		in >> n_precedences;

		assert(0 <= n_precedences && n_precedences <= 200);

		precedences_.clear();
		precedences_.resize(n_beverages);
		for (Size i = 0; i < n_precedences; ++i)
		{
			std::string b1, b2;
			in >> b1 >> b2;
			precedences_[beverage_index(b1)].push_back(beverage_index(b2));
		}

		return true;
	}
	
	Size beverage_index(const std::string& b) const
	{
		const auto pos = std::find(beverages_.begin(), beverages_.end(), b);
		assert(pos != beverages_.end());
		
		return static_cast<Size>(pos - beverages_.begin());
	}

	virtual void solve(std::ostream& out, unsigned int i_case) const override
	{
		out << "Case #" << i_case + 1 << ": Dilbert should drink beverages in this order: ";

		const auto drink_order = topologic_sort(precedences_);
		print_join_transform(out, drink_order.begin(), drink_order.end(),
			[this](Size i) { return beverages_[i]; });

		out << ".\n\n";
	}

private:
	std::vector<std::string> beverages_;
	Adjacency_list precedences_;
};

int main()
{
	CP p;
	return p.run();
}

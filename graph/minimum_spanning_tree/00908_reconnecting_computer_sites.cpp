/*********************************************************************
Re-connecting computer sites
----------------------------
UVa ID: 009 08

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "io.hpp"
#include <algorithm>
#include <cassert>
#include <numeric>
#include <vector>
#include <utility>

using Size = unsigned int;
using Weight = unsigned int;

class Disjoint_set
{
public:
	// Creates a disjoint set of (n) disjoint elements
	Disjoint_set(Size n)
	{
		sizes_.assign(n, 1);
		parents_.resize(n);
		std::iota(parents_.begin(), parents_.end(), static_cast<Size>(0));
	}

	// Unites two elements and returns the size of the new set
	Size unite(Size x, Size y)
	{
		auto px = find_parent(x);
		auto py = find_parent(y);
		assert(px != py);

		if (sizes_[py] < sizes_[px])
			std::swap(px, py);

		parents_[px] = py;
		sizes_[py] += sizes_[px];

		return sizes_[py];
	}

	bool is_same_set(Size x, Size y) const
	{
		return find_parent(x) == find_parent(y);
	}

private:
	Size find_parent(Size x) const
	{
		auto& parent = parents_[x];
		if (parent != x)
			parent = find_parent(parent);

		return parent;
	}

private:
	std::vector<Size> sizes_;
	mutable std::vector<Size> parents_;
};

struct Edge
{
	Size vertex1;
	Size vertex2;
	Weight weight;
	
	bool operator<(const Edge& other) const
	{
		return weight < other.weight;
	}
};

std::istream& operator>>(std::istream& in, Edge& edge)
{
	in >> edge.vertex1 >> edge.vertex2 >> edge.weight;
	--edge.vertex1;			// To zero-based indexing
	--edge.vertex2;

	return in;
}

// Returns the weight of the minimum spanning tree
// using the Kruskals's algorithm
Weight min_span_tree_weight(Size n_vertices, const std::vector<Edge>& graph)
{
	auto gr = graph;
	std::sort(gr.begin(), gr.end());

	Disjoint_set ds(n_vertices);

	Weight min_weight = 0;
	for (const auto& edge : gr)
		if (!ds.is_same_set(edge.vertex1, edge.vertex2))
		{
			min_weight += edge.weight;
			if (ds.unite(edge.vertex1, edge.vertex2) == n_vertices)
				break;
		}

	return min_weight;
}

class CP : public CP2
{
private:
	virtual bool read_input(std::istream& in) override
	{
		if (!(in >> n_computers_))
			return false;

		assert(1 <= n_computers_ && n_computers_ <= 1'000'000);

		original_cost_ = 0;
		for (Size i = 1; i < n_computers_; ++i)
		{
			Edge line;
			in >> line;
			original_cost_ += line.weight;
		}

		Size n_lines;
		in >> n_lines;

		assert(1 <= n_lines && n_lines <= 10);
		read_vector(in, n_lines, lines_);

		in >> n_lines;

		assert(n_computers_ - 1 <= n_lines && n_lines <= n_computers_ * (n_computers_ - 1) / 2);
		read_vector(in, n_lines, lines_, true /* append */);

		return true;
	}

	virtual void solve(std::ostream& out, unsigned int i_case) const override
	{
		if (i_case > 0)
			out << '\n';

		out << original_cost_ << '\n'
			<< min_span_tree_weight(n_computers_, lines_) << '\n';
	}

private:
	Size n_computers_;
	Weight original_cost_;
	std::vector<Edge> lines_;
};

int main()
{
	CP p;
	return p.run();
}

/*********************************************************************
Ants colony
-----------
UVa ID: 122 38

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "bit.hpp"
#include "matrix.hpp"
#include "util.hpp"
#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

using Length = unsigned long long;
using Path = std::pair<std::size_t, std::size_t>;
using Edge = std::pair<std::size_t, Length>;
using Adjacency_list = std::vector<std::vector<Edge>>;

class Path_length
{
public:
	Path_length(const Adjacency_list& graph) : graph_(graph)
	{
		const auto n_vertices = graph_.size();
		indices_.resize(n_vertices);
		lengths_.resize(n_vertices);

		const auto n = 2 * n_vertices - 1;
		depths_.reserve(n);
		lengths_ind_.reserve(n);

		lengths_[0] = 0;
		depth_first_search(0, 0);
		build_sparse_table();
	}

	Length length(Path path) const
	{
		auto first = indices_[path.first];
		auto last = indices_[path.second];

		sort2(first, last);
		const auto lca_index = min_depth_index(first, last + 1);
		return lengths_ind_[first] + lengths_ind_[last] // -
			   - 2 * lengths_ind_[lca_index];
	}

private:
	void depth_first_search(std::size_t vertex, std::size_t parent, std::size_t depth = 0)
	{
		add_to_lists(vertex, depth);
		for (const auto& edge : graph_[vertex])
			if (edge.first != parent)
			{
				lengths_[edge.first] = lengths_[vertex] + edge.second;
				depth_first_search(edge.first, vertex, depth + 1);
				add_to_lists(vertex, depth);
			}
	}

	void add_to_lists(std::size_t vertex, std::size_t depth)
	{
		indices_[vertex] = depths_.size();
		lengths_ind_.push_back(lengths_[vertex]);
		depths_.push_back(depth);
	}

	void build_sparse_table()
	{
		const auto n = depths_.size();
		const auto m = floor_log2(n) + 1;
		depth_sparse_table_.resize(n, m);

		for (std::size_t i = 0; i < n; ++i)
			depth_sparse_table_(i, 0) = i;

		for (unsigned int lev = 1; lev < m; ++lev)
			build_sparse_table(n, lev);
	}

	void build_sparse_table(std::size_t n, unsigned int lev)
	{
		const auto two_to_k = pow2<std::size_t>(lev);
		for (std::size_t i = 0; i + two_to_k - 1 < n; ++i)
		{
			const auto i1 = depth_sparse_table_(i, lev - 1);
			const auto i2 = depth_sparse_table_(i + two_to_k / 2, lev - 1);

			depth_sparse_table_(i, lev) = index_by_min_depth(i1, i2);
		}
	}

	// Returns the index of the smallest element in the range [first, last)
	std::size_t min_depth_index(std::size_t first, std::size_t last) const
	{
		assert(first < last);

		const auto lev = floor_log2(last - first);
		const auto i1 = depth_sparse_table_(first, lev);
		const auto i2 = depth_sparse_table_(last - pow2<std::size_t>(lev), lev);

		return index_by_min_depth(i1, i2);
	}

	std::size_t index_by_min_depth(std::size_t index1, std::size_t index2) const
	{
		return depths_[index1] <= depths_[index2] ? index1 : index2;
	}

private:
	const Adjacency_list& graph_;
	std::vector<Length> lengths_;

	// Sparse table for the (depths) array: entry (i, lev) is
	// the index of smallest element in the range [i .. i + 2^lev)
	Matrix<std::size_t> depth_sparse_table_;

	std::vector<std::size_t> indices_;
	std::vector<Length> lengths_ind_; // lengths_ind[indices[vertex]] = lengths[vertex]
	std::vector<std::size_t> depths_;
};

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::size_t n_anthills;
		if (!read(n_anthills) || n_anthills == 0)
			return false;

		assert(2 <= n_anthills && n_anthills <= 100'000);

		tunnels_.clear();
		tunnels_.resize(n_anthills);

		for (std::size_t i = 1; i < n_anthills; ++i)
		{
			std::size_t a;
			Length len;
			read(a, len);
			assert(a < i && 1 <= len && len <= 1'000'000'000);

			tunnels_[i].push_back({a, len});
			tunnels_[a].push_back({i, len});
		}

		return read_size_vec(quieries_);
	}

	virtual void solve(unsigned int) override
	{
		const Path_length path_len(tunnels_);

		const auto path_length = [&path_len](const Path& path) { return path_len.length(path); };

		write_vec(quieries_, path_length, ' ');
		write_ln();
	}

private:
	Adjacency_list tunnels_;
	std::vector<Path> quieries_;
};

MAIN

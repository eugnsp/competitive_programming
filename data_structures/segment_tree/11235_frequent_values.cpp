/*********************************************************************
Frequent values
---------------
UVa ID: 112 35

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "range.hpp"
#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>
#include <utility>

using Seg = Range<std::size_t>;

class Segment_tree
{
public:
	Segment_tree(const std::vector<std::size_t>& data) : data_(data)
	{
		tree_.resize(get_tree_size());
		build({0, data_.size()});
	}

	// Returns zero is the range is empty
	std::size_t max_element(Seg query) const
	{
		return max_element(query, {0, data_.size()});
	}

private:
	std::size_t get_tree_size() const
	{
		std::size_t n_nodes = 1;
		while (n_nodes < data_.size())
			n_nodes *= 2;
		return 2 * n_nodes;
	}

	void build(Seg range, std::size_t root_index = 1)
	{
		if (size(range) == 1)
			tree_[root_index] = data_[range.begin];
		else
		{
			const auto left_index = 2 * root_index;
			const auto right_index = left_index + 1;

			build(left_half(range), left_index);
			build(right_half(range), right_index);

			tree_[root_index] = std::max(tree_[left_index], tree_[right_index]);
		}
	}

	std::size_t max_element(Seg query, Seg current, std::size_t root_index = 1) const
	{
		if (!intersects(current, query))
			return 0;

		if (includes(current, query))
			return tree_[root_index];

		const auto left_index = 2 * root_index;
		const auto right_index = left_index + 1;

		const auto left = max_element(query, left_half(current), left_index);
		const auto right = max_element(query, right_half(current), right_index);

		return std::max(left, right);
	}

private:
	const std::vector<std::size_t>& data_;
	std::vector<std::size_t> tree_;
};

class CP : public CP2
{
private:
	virtual bool read_input(std::istream& in) override
	{
		std::size_t n, nq;
		in >> n;
		if (n == 0)
			return false;

		in >> nq;
		assert(n <= 100000 && nq <= 100000);

		an_.resize(n);
		for (auto& a : an_)
			in >> a;

		assert(std::is_sorted(an_.begin(), an_.end()));

		queries_.clear();
		queries_.reserve(nq);
		for (std::size_t i = 0; i < nq; ++i)
		{
			std::size_t begin, end;
			in >> begin >> end;
			assert(begin > 0 && begin <= end && end <= n);
			queries_.push_back({--begin, end});	// To zero-based indexing
		}

		return true;
	}

	virtual void solve(std::ostream& out, unsigned int) const override
	{
		std::vector<std::size_t> n_adj_eq_vals(an_.size());

		n_adj_eq_vals[0] = 1;
		for (std::size_t i = 1, count = 1; i < an_.size(); ++i)
			n_adj_eq_vals[i] = (an_[i] == an_[i - 1]) ? ++count : (count = 1);

		const Segment_tree seg_tree(n_adj_eq_vals);
		for (const auto& q : queries_)
		{
			// Process equal elements at the beginning separately
			const auto begin = q.begin;
			const auto first_a = an_[begin];
			const std::size_t new_begin = std::find_if(an_.begin() + q.begin, an_.begin() + q.end,
				[first_a](int v) { return v != first_a; }) - an_.begin();

			const auto n_head = new_begin - begin;
			const auto n_tail = seg_tree.max_element({new_begin, q.end});

			out << std::max(n_head, n_tail) << '\n';
		}
	}

private:
	std::vector<int> an_;
	std::vector<Seg> queries_;
};

int main()
{
	CP p;
	return p.run();
}

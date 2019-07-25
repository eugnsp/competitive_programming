/*********************************************************************
Census
------
UVa ID: 112 97

This year, there have been many problems with population calculations,
since in some cities, there are many emigrants, or the population
growth is very high. Every year the ACM (for Association for Counting
Members) conducts a census in each region. The country is divided into
N^2 regions, consisting of an NxN grid of regions. Your task is to
find the least, and the greatest population in some set of regions.
Since in a single year there is no significant change in the
populations, the ACM modifies the population counts by some number
of inhabitants.

Input
-----

In the first line you will find N (0 <= N <= 500), in following the N
lines you will be given N numbers, wich represent, the initial
population of city C[i, j]. In the following line is the number Q
(Q <= 40000), followed by Q lines with queries. There are two possible
queries:
	* "q x1 y1 x2 y2" which represent the coordinates of the upper
	  left and lower right of where you must calculate the maximum
	  and minimum change in population.
	* "c x y v" indicating a change of the population of city C[x, y]
	  by value v.

Output
------

For each query, "q x1 y1 x2 y2" print in a single line the greatest
and least amount of current population. Separated each output by a
space. Note: There is only a single test case.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <limits>
#include <utility>
#include <variant>

using Pos = Position<std::size_t>;

struct Rect
{
	Pos top_left;
	Pos bottom_right;
};

template<typename T>
class Counter
{
public:
	Counter(Matrix<T> init_values) : values_(std::move(init_values))
	{
		assert(values_.rows() == values_.cols());
		size_ = values_.rows();
		b_size_ = static_cast<std::size_t>(std::ceil(std::sqrt(size_)));

		const auto n_blocks = size_ / b_size_;
		min_maxs_.resize(n_blocks, n_blocks);

		for (std::size_t b_col = 0; b_col < n_blocks; ++b_col)
			for (std::size_t b_row = 0; b_row < n_blocks; ++b_row)
			{
				auto min_max = min_max_init();

				for (std::size_t col = b_col * b_size_; col < (b_col + 1) * b_size_; ++col)
					for (std::size_t row = b_row * b_size_; row < (b_row + 1) * b_size_; ++row)
						update_min_max(min_max, values_(row, col));

				min_maxs_(b_row, b_col) = min_max;
			}
	}

	std::pair<T, T> min_max(Rect rect) const
	{
		const auto first_row = rect.top_left.row;
		const auto first_col = rect.top_left.col;
		const auto last_row = rect.bottom_right.row + 1;
		const auto last_col = rect.bottom_right.col + 1;

		auto min_max = min_max_init();

		for (auto col = first_col; col < std::min(last_col, block_ceil(first_col) * b_size_); ++col)
			for (auto row = first_row; row < last_row; ++row)
				update_min_max(min_max, values_(row, col));

		for (auto col = std::max(first_col, block_floor(last_col) * b_size_); col < last_col; ++col)
			for (auto row = first_row; row < last_row; ++row)
				update_min_max(min_max, values_(row, col));

		for (auto col = first_col; col < last_col; ++col)
			for (auto row = first_row; row < std::min(last_row, block_ceil(first_row) * b_size_); ++row)
				update_min_max(min_max, values_(row, col));

		for (auto col = first_col; col < last_col; ++col)
			for (auto row = std::max(first_row, block_floor(last_row) * b_size_); row < last_row; ++row)
				update_min_max(min_max, values_(row, col));

		for (auto b_col = block_ceil(first_col); b_col < last_col / b_size_; ++b_col)
			for (auto b_row = block_ceil(first_row); b_row < last_row / b_size_; ++b_row)
			{
				min_max.first = std::min(min_max.first, min_maxs_(b_row, b_col).first);
				min_max.second = std::max(min_max.second, min_maxs_(b_row, b_col).second);
			}

		return min_max;
	}

	void set(Pos pos, const T& new_value)
	{
		values_(pos) = new_value;

		const auto b_row = pos.row / b_size_;
		const auto b_col = pos.col / b_size_;
		if (const auto n_blocks = size_ / b_size_; b_row >= n_blocks || b_col >= n_blocks)
			return;

		// Update the block that contains this value
		auto min_max = min_max_init();
		for (auto col = b_col * b_size_; col < (b_col + 1) * b_size_; ++col)
			for (auto row = b_row * b_size_; row < (b_row + 1) * b_size_; ++row)
				update_min_max(min_max, values_(row, col));

		min_maxs_(b_row, b_col) = min_max;
	}

private:
	static std::pair<T, T> min_max_init()
	{
		return {std::numeric_limits<T>::max(), std::numeric_limits<T>::min()};
	}

	static void update_min_max(std::pair<T, T>& min_max, T value)
	{
		min_max.first = std::min(min_max.first, value);
		min_max.second = std::max(min_max.second, value);
	}

	std::size_t block_floor(std::size_t index) const
	{
		return (index - 1) / b_size_;
	}

	std::size_t block_ceil(std::size_t index) const
	{
		return block_floor(index + b_size_);
	}

private:
	std::size_t size_;
	std::size_t b_size_;

	Matrix<T> values_;
	Matrix<std::pair<T, T>> min_maxs_;
};

using T = unsigned int;

class CP : public CP3
{
private:
	virtual void read_input() override
	{
		std::size_t n;
		read(n);

		population_.resize(n, n);
		read_matrix(population_);

		read(n);
		while (n-- > 0)
		{
			char type;
			read(type);
			if (type == 'q')
			{
				Rect rect;
				read(rect.top_left, rect.bottom_right);
				rect.top_left.to_zero_based();
				rect.bottom_right.to_zero_based();
				queries_.emplace_back(rect);
			}
			else if (type == 'c')
			{
				std::pair<Pos, T> q;
				read(q.first, q.second);
				q.first.to_zero_based();
				queries_.emplace_back(q);
			}
		}
	}

	virtual void solve() override
	{
		Counter<T> counter(population_);

		for (const auto& q : queries_)
			if (q.index() == 0)
			{
				auto ans = counter.min_max(std::get<0>(q));
				write_ln(ans.second, ' ', ans.first);
			}
			else if (q.index() == 1)
				counter.set(std::get<1>(q).first, std::get<1>(q).second);
	}

private:
	Matrix<T> population_;
	std::vector<std::variant<Rect, std::pair<Pos, T>>> queries_;
};

MAIN

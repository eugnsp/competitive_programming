/*********************************************************************
Getting in line
---------------
UVa ID: 002 16

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "bit_mask.hpp"
#include "matrix.hpp"
#include "point.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <limits>
#include <type_traits>
#include <vector>

constexpr auto invalid_vertex = static_cast<std::size_t>(-1);

template<class Weight_fn>
auto hamiltonian_paths_matrix(std::size_t n, Weight_fn weight, std::size_t start = invalid_vertex)
{
	assert(n > 1);

	using Weight = std::invoke_result_t<Weight_fn, std::size_t, std::size_t>;
	const auto max_weight = std::numeric_limits<Weight>::max();

	// mw(i, mask) is the minimum weight of the path that visits all the vertices
	// in the (mask) (including the last one) and ends at the vertex (i),
	// if (start) is a valid vertex index, the path is constrained to start at that vertex.

	Matrix<Weight> mw(n, Bit_mask(n).size(), max_weight);

	// The recurrence relation is:
	// mw(i, mask) = min {j != i : mask[j]} [weight_ij + mw(j, mask.reset[i])]
	//							if count(mask) > 1 && mask[i].
	//
	// The base case:
	// mw(i, i-th bit set) = 0	for all (i) if (start) is invalid, or (i) = (start) otherwise
	// mw(i, mask) = <infty>	otherwise

	if (start >= n)
		for (std::size_t i = 0; i < n; ++i)
			mw(i, Bit_mask(n).set(i)) = 0;
	else
		mw(start, Bit_mask(n).set(start)) = 0;

	const auto full_mask = Bit_mask(n).set();
	for (Bit_mask mask(n, 1); mask <= full_mask; ++mask)
		for (std::size_t i = 0; i < n; ++i)
		{
			if (!mask[i])
				continue;

			for (std::size_t j = 0; j < n; ++j)
			{
				if (j == i || !mask[j])
					continue;

				auto mask_without_ith = mask;
				mask_without_ith.reset(i);

				const auto path_weight = mw(j, mask_without_ith);
				if (path_weight != max_weight)
					mw(i, mask) = std::min(mw(i, mask), path_weight + weight(i, j));
			}
		}

	return mw;
}

template<class Weight_fn>
auto shortest_hamiltonian_path(std::size_t n, Weight_fn weight)
{
	using Weight = std::invoke_result_t<Weight_fn, std::size_t, std::size_t>;

	auto mw = hamiltonian_paths_matrix(n, weight);

	const auto max_weight = std::numeric_limits<Weight>::max();
	auto min_weight = max_weight;
	auto last = invalid_vertex;

	for (std::size_t i = 0; i < n; ++i)
	{
		const auto path_weight = mw(i, Bit_mask(n).set());
		if (path_weight < min_weight)
		{
			min_weight = path_weight;
			last = i;
		}
	}
	assert(last != invalid_vertex);

	std::vector<std::size_t> path{last};
	path.reserve(n);

	auto mask = Bit_mask(n).set();
	while (true)
	{
		bool found = false;
		for (std::size_t j = 0; j < n; ++j)
		{
			if (j == last || !mask[j])
				continue;

			auto mask_without_last = mask;
			mask_without_last.reset(last);

			const auto path_weight = mw(j, mask_without_last);
			assert(path_weight != max_weight);

			if (mw(last, mask) == path_weight + weight(last, j))
			{
				found = true;
				path.push_back(j);
				mask = mask_without_last;
				last = j;
				break;
			}
		}

		if (!found)
			break;
	}

	assert(path.size() == n);
	return std::make_pair(min_weight, path);
}

using Pt = Point<unsigned int>;

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_size_vec(points_);
	}

	virtual void solve(unsigned int i_case) override
	{
		write(std::fixed, std::setprecision(2));
		write_ln("**********************************************************");
		write_ln("Network #", i_case);

		const auto dist = [this](auto i, auto j) { return 16. + distance(points_[i], points_[j]); };
		const auto line = shortest_hamiltonian_path(points_.size(), dist);

		for (std::size_t j = 0; j < line.second.size() - 1; ++j)
		{
			const auto from = line.second[j];
			const auto to = line.second[j + 1];
			write_ln("Cable requirement to connect (", points_[from].x, ',', points_[from].y,
				") to (", points_[to].x, ',', points_[to].y, ") is ", dist(from, to), " feet.");
		}
		write_ln("Number of feet of cable required is ", line.first, '.');
	}

private:
	std::vector<Pt> points_;
};

MAIN

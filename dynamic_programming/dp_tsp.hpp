// Dynamic programming TSP common routines
//
// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include "bit_mask.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <utility>
#include <limits>
#include <functional>
#include <algorithm>
#include <vector>
#include <cassert>

constexpr auto invalid_vertex = static_cast<std::size_t>(-1);

template<class Weight_func>
Matrix<typename std::result_of<Weight_func(std::size_t, std::size_t)>::type>
	hamiltonian_paths_matrix(std::size_t n, Weight_func weight, std::size_t start = invalid_vertex)
{
	assert(n > 1);

	using Weight = typename std::result_of<Weight_func(std::size_t, std::size_t)>::type;
	const auto max_weight = std::numeric_limits<Weight>::max();

	// mw(i, mask) is the minimum weight of the path that visits all the vertices
	// in the (mask) (including the last one) and ends at the vertex (i),
	// if (start) is a valid vertex index, the path is constrained to start at that vertex.

	Matrix<Weight> mw(n, Bit_mask(n).size(), max_weight);

	// The recurrence relation is:
	// mw(i, mask) = min {j != i : mask[j]} [weight_ij + mw(j, mask with mask[i] reset)]
	//							if count(mask) > 1 && mask[i].
	//
	// Base case:
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

template<class Weight_func>
typename std::result_of<Weight_func(std::size_t, std::size_t)>::type
	shortest_hamiltonian_path_weight(std::size_t n, Weight_func weight)
{
	using Weight = typename std::result_of<Weight_func(std::size_t, std::size_t)>::type;

	auto mw = hamiltonian_paths_matrix(n, weight);

	auto min_weight = std::numeric_limits<Weight>::max();
	for (std::size_t i = 0; i < n; ++i)
		min_weight = std::min(min_weight, mw(i, Bit_mask(n).set()));

	return min_weight;
}

template<class Weight_func>
std::pair<
	typename std::result_of<Weight_func(std::size_t, std::size_t)>::type,
	std::vector<std::size_t>>
	shortest_hamiltonian_path(std::size_t n, Weight_func weight)
{
	using Weight = typename std::result_of<Weight_func(std::size_t, std::size_t)>::type;

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
	for (;;)
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
	return {min_weight, path};
}

template<class Weight_func>
typename std::result_of<Weight_func(std::size_t, std::size_t)>::type
	shortest_hamiltonian_cycle_weight(std::size_t n, Weight_func weight)
{
	using Weight = typename std::result_of<Weight_func(std::size_t, std::size_t)>::type;

	auto mw = hamiltonian_paths_matrix(n, weight, 0);

	const auto max_weight = std::numeric_limits<Weight>::max();
	auto min_weight = max_weight;
	for (std::size_t i = 1; i < n; ++i)
	{
		const auto path_weight = mw(i, Bit_mask(n).set());
		assert(path_weight != max_weight);
		min_weight = std::min(min_weight, path_weight + weight(0, i));
	}

	return min_weight;
}

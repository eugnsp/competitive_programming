/*********************************************************************
Allergy test
------------
UVa ID: 116 91

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "bit_mask.hpp"
#include "matrix.hpp"
#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

class CP : public CP1
{
private:
	static constexpr std::size_t max_size = static_cast<std::size_t>(-1);

private:
	virtual void read_input() override
	{
		read(n_allergens_);
		assert(between(n_allergens_, 1, 20));

		durations_.resize(n_allergens_);
		for (auto& d : durations_)
		{
			read(d);
			assert(1 <= d && d <= 7);
		}
	}

	virtual void solve(unsigned int) override
	{
		/*********************************************************************
		ml(mask, overlap) is the day at which the next test can be started,
			such that it overlaps by up to (overlap) days with the last one.

		The recurrence relation:
			ml(mask, overlap) = 1 + prev_overlap +
						+ min {i : !mask[i]} ml(mask.set[i], prev_overlap),
				where prev_overlap = max(durations[i] - overlap - 1, 0)
				is the maximum possible overlap with the previous test.

		The base case:
			ml(mask, overlap) = 0	if no tests remain (all bits in
														the (mask) are set).
		**********************************************************************/

		max_duration_ = *std::max_element(durations_.begin(), durations_.end());

		const auto n = Bit_mask(n_allergens_).size();
		ml_.resize_and_fill(n, max_duration_, max_size);

		const auto no_allergens_mask = Bit_mask(n_allergens_);
		write_ln(min_length(no_allergens_mask, 0));
	}

	std::size_t min_length(const Bit_mask& used_allergens, std::size_t overlap)
	{
		auto& m = ml_(used_allergens, overlap);
		if (m != max_size)
			return m;

		if (used_allergens.all())
			return (m = 0);

		// It is enough to try each duration only once
		std::vector<bool> tried_durations(max_duration_, false);

		for (std::size_t i = 0; i < n_allergens_; ++i)
		{
			const auto duration = durations_[i];
			if (used_allergens[i] || tried_durations[duration - 1])
				continue;

			const auto with_ith_allergen = used_allergens.with_set(i);
			const auto prev_overlap = (duration > overlap) ? duration - overlap - 1 : 0;
			m = std::min(m, min_length(with_ith_allergen, prev_overlap) + 1 + prev_overlap);

			tried_durations[duration - 1] = true;
		}

		return m;
	}

private:
	std::size_t n_allergens_;
	std::vector<std::size_t> durations_;
	std::size_t max_duration_;
	Matrix<std::size_t> ml_;
};

MAIN


/*********************************************************************
Minimum number of jumps
-----------------------

For the given an array of integers in which each element represents
the maximum number of steps that can be made forward from that element
find the minimum number of jumps to reach the end of the array from
the first element.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <optional>
#include <vector>

template<typename T>
std::optional<T> count_min_number_of_jumps(const std::vector<T>& max_n_jumps)
{
	if (max_n_jumps.empty())
		return {};

	T n_jumps = 0;

	const auto n = max_n_jumps.size() - 1;
	for (T i = 0, max_i = 0, n_steps = 0; i < n; ++i)
	{
		max_i = std::max(max_i, i + max_n_jumps[i]);
		if (n_steps == 0)
		{
			if (i >= max_i)
				return {};
			n_steps = max_i - i;
			++n_jumps;
		}
		--n_steps;
	}

	return n_jumps;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(max_n_jumps_);
	}

	virtual void solve(unsigned int) override
	{
		const auto n_jumps = count_min_number_of_jumps(max_n_jumps_);
		if (n_jumps)
			write_ln(*n_jumps);
		else
			write_ln(-1);
	}

private:
	std::vector<unsigned int> max_n_jumps_;
};

MAIN

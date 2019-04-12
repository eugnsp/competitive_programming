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

	constexpr auto inf = static_cast<T>(-1);

	const auto n = max_n_jumps.size();
	std::vector<T> b(n, inf);
	b[0] = 0;

	for (T i = 1; i < n; ++i)
		for (T j = 0; j < i; ++j)
			if (b[j] != inf && max_n_jumps[j] >= i - j)
				b[i] = std::min(b[i], b[j] + 1);

	if (b.back() != inf)
		return b.back();
	else
		return {};
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

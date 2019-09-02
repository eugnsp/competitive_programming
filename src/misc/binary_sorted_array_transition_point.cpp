/*********************************************************************
Binary sorted array transition point
------------------------------------

Find the transition point in the given binary sorted array.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <vector>

template<class It>
It transition_point(It first, It last)
{
	// Loop invariants:
	// 	[first0, first): 	contains zeros
	// 	[first, last)`: 	is not yet processed
	// 	[last, last0): 		contains ones

	while (first != last)
	{
		const auto mid = first + (last - first) / 2;
		if (*mid)
			last = mid;
		else
			first = mid + 1;
	}

	return first;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(seq_);
	}

	virtual void solve(unsigned int) override
	{
		auto pos = transition_point(seq_.begin(), seq_.end());
		write_ln(pos - seq_.begin());
	}

private:
	std::vector<unsigned int> seq_;
};

MAIN

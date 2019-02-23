/*********************************************************************
Jill rides again
----------------
UVa ID: 005 07

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_kadane_max_sum.hpp"
#include <cstddef>
#include <vector>
#include <cassert>

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t n_stops;
		read(n_stops);
		assert(n_stops >= 2);

		nicenesses_.resize(n_stops - 1);
		for (auto& n : nicenesses_)
			read(n);
	}

	virtual void solve(unsigned int i_case) override
	{
		const auto max_sum = kadane_max_sum_and_range(nicenesses_.cbegin(), nicenesses_.cend());

		if (max_sum.first > 0)
			write_ln(
				"The nicest part of route ",
				i_case + 1,
				" is between stops ",
				std::distance(nicenesses_.cbegin(), max_sum.second.first) + 1,
				" and ",
				std::distance(nicenesses_.cbegin(), max_sum.second.second) + 1);
		else
			write_ln("Route ", i_case + 1, " has no nice parts");
	}

private:
	std::vector<int> nicenesses_;
};

MAIN(CP)

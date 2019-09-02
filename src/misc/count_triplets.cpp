/*********************************************************************
Count the triplets
------------------

For the given array of distinct integers count all the triplets such
that the sum of two elements equals the third element.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <vector>

template<class It, typename T>
std::size_t count_sums(It first, It last, T sum)
{
	if (first == last)
		return 0;

	std::size_t count = 0;

	--last;
	while (first != last)
	{
		const auto s = *first + *last;
		if (s == sum)
			++count;

		if (s < sum)
			++first;
		else // s >= sum
			--last;
	}

	return count;
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
		std::sort(seq_.begin(), seq_.end());

		std::size_t triplet_count = 0;
		for (auto it = seq_.begin(); it != seq_.end(); ++it)
			triplet_count += count_sums(seq_.begin(), seq_.end(), *it);

		write_ln(triplet_count);
	}

private:
	std::vector<unsigned int> seq_;
};

MAIN

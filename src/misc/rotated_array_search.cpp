/*********************************************************************
Rotated array search
--------------------

Find the given element in the given rotated array.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <vector>

// Finds element in a rotated non-decreasing sorted range [first, last),
// return the iterator to an arbitrary element that is equal to (value),
// returns (last) if no such element exists
template<class It, typename T>
It find_rotated(It first, const It last, const T& value)
{
	auto end = last;
	while (first != end)
	{
		const auto mid = first + (end - first) / 2;
		if (value == *mid)
			return mid;

		if (*first < *mid) // Left half is sorted
		{
			if (value >= *first && value < *mid)
			{
				const auto pos = std::lower_bound(first, mid, value);
				return (pos != mid && *pos == value) ? pos : last;
			}
			first = mid + 1;
		}
		else if (*mid < *first) // Right half is sorted
		{
			if (value > *mid && value <= *(end - 1))
			{
				const auto pos = std::lower_bound(mid + 1, end, value);
				return (pos != end && *pos == value) ? pos : last;
			}
			end = mid;
		}
		else // Don't know which half is sorted
			++first;
	}

	return last;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(seq_);
		read(n_);
	}

	virtual void solve(unsigned int) override
	{
		const auto pos = find_rotated(seq_.begin(), seq_.end(), n_);
		if (pos != seq_.end())
			write_ln(pos - seq_.begin());
		else
			write_ln(-1);
	}

private:
	std::vector<int> seq_;
	int n_;
};

MAIN

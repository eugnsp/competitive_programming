/*********************************************************************
Age sort
--------
UVa ID: 114 62

You are given the ages (in years) of all people of a country with at
least 1 year of age. You know that no individual in that country lives
for 100 or more years. Now, you are given a very simple task of
sorting all the ages in ascending order.

Input
-----
There are multiple test cases in the input file. Each case starts with
an integer N (0 < N <= 2'000'000), the total number of people. In the
next line, there are N integers indicating the ages. Input is
terminated with a case where N = 0. This case should not be processed.

Output
------
For each case, print a line with N space separated integers. These
integers are the ages of that country sorted in ascending order.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "util.hpp"
#include <cassert>
#include <vector>

using Age = unsigned int;
using Count = unsigned int;

template<typename T>
struct Id
{
	using Type = T;
};

template<typename T>
void count_sort(std::vector<T>& values, typename Id<T>::Type min_value,
				typename Id<T>::Type max_value)
{
	const auto range_size = max_value - min_value + 1;
	std::vector<Count> counts(range_size, 0);
	for (auto v : values)
	{
		assert(between(v, min_value, max_value));
		++counts[v - min_value];
	}

	values.clear();
	for (auto r = min_value; r <= max_value; ++r)
		for (Count i = 0; i < counts[r - min_value]; ++i)
			values.push_back(r);
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_size_vec(ages_);
	}

	virtual void solve(unsigned int) override
	{
		count_sort(ages_, 1, 99);
		write_vec(ages_, ' ');
		write_ln();
	}

private:
	std::vector<Age> ages_;
};

MAIN

/*********************************************************************
Majority element
----------------
URL: https://practice.geeksforgeeks.org/problems/majority-element/0

Find the majority element in the given array of size N. A majority
element is an element that appears more than N/2 times in the array.

Input
-----
The first line of the input contains T denoting the number of test
cases. The first line of the test case will be the size of array and
second line will be the elements of the array.

Output
------
For each test case the output will be the majority element of the
array. Output "-1" if no majority element is there in the array.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <vector>

using Element = unsigned int;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(seq_);
	}

	virtual void solve(unsigned int) override
	{
		Element majority_candidate;
		std::size_t counter = 0;

		for (const auto v : seq_)
		{
			if (counter == 0)
				majority_candidate = v;
			if (v == majority_candidate)
				++counter;
			else
				--counter;
		}

		counter = std::count(seq_.begin(), seq_.end(), majority_candidate);

		if (counter > seq_.size() / 2)
			write_ln(majority_candidate);
		else
			write_ln(-1);
	}

private:
	std::vector<Element> seq_;
};

MAIN(CP)

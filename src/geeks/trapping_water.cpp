/*********************************************************************
Count smaller elements on the right side
----------------------------------------
URL: https://practice.geeksforgeeks.org/problems/count-smaller-elements/0

Given an array A of N integers. For each element of the array count
the number of smaller elements on the right side of this element.

Input
-----
The first line of input contains an integer T denoting the number of
test cases. Then T test cases follow. The first line of each test case
contains an integer N denoting the size of the array A in the next
line are N space separated values of the array A.

Output
------
For each test case output the numbers of smaller elements.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <vector>

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(heights_);
	}

	virtual void solve(unsigned int) override
	{
		std::vector<std::size_t> max_left(heights_.size(), 0);
		std::vector<std::size_t> max_right(heights_.size(), 0);

		max_left.front() = heights_.front();
        max_right.back() = heights_.back();
		for (std::size_t i = 1, j = heights_.size() - 2; i < heights_.size(); ++i, --j)
		{
			max_left[i] = std::max(max_left[i - 1], heights_[i]);
			max_right[j] = std::max(max_right[j + 1], heights_[j]);
		}

		std::size_t volume = 0;
		for (std::size_t i = 1; i < heights_.size() - 1; ++i)
		{
			const auto min = std::min(max_left[i], max_right[i]);
			volume += min - heights_[i];
		}

		write_ln(volume);
	}

private:
	std::vector<std::size_t> heights_;
};

MAIN(CP)

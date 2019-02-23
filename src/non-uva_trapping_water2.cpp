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
		std::size_t left = 0;
		std::size_t right = heights_.size();

		std::size_t max_left = heights_.front();
		std::size_t max_right = heights_.back();

		std::size_t volume = 0;
		while (left < right)
			if (max_left < max_right)
			{
				max_left = std::max(max_left, heights_[left]);
				volume += max_left - heights_[left];
				++left;
			}
			else
			{
				max_right = std::max(max_right, heights_[right - 1]);
				volume += max_right - heights_[right - 1];
				--right;
			}

		write_ln(volume);
	}

private:
	std::vector<std::size_t> heights_;
};

MAIN(CP)

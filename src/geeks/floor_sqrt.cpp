/*********************************************************************
Square root
-----------
URL: https://practice.geeksforgeeks.org/problems/square-root/1

Given an integer x, your task is to find the square root of it. If
x is not a perfect square, then return floor(sqrt(x)).

Input
-----
First line of input contains number of testcases T. For each testcase,
the only line contains the number x.

Output
------
For each testcase, print square root of given integer.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"

unsigned int floor_sqrt(unsigned int x)
{
	unsigned int left = 0;
	unsigned int right = x;

	// left ^ 2 <= x, (right + 1) ^ 2 > x

	// At the beginning: left = 0, right = x
	// At the end: left = right = floor(sqrt(x))

	while (left != right)
	{
		auto mid = (left + right + 1) / 2;
		if (mid * mid <= x)
			left = mid;
		else
			right = mid - 1;
	}

	return left;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(x_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(floor_sqrt(x_));
	}

private:
	unsigned int x_;
};

MAIN(CP)

/*********************************************************************
Merge two strings
-----------------
URL: https://practice.geeksforgeeks.org/problems/merge-two-strings/0

Given two strings S1 and S2 as input, the task is to merge them
alternatively i.e. the first character of S1 then the first character
of S2 and so on till the strings end. Add the whole string if other
string is empty.

Input
-----
The first line of input contains an integer T denoting the number of
test cases. Then T test cases follow. Each test case contains two
strings S1 and S2.

Output
------
For each test case, in a new line, print the merged string.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <string>

std::string merge(const std::string& s1, const std::string& s2)
{
	std::string str;
	str.reserve(s1.size() + s2.size());

	auto it1 = s1.begin();
	auto it2 = s2.begin();
	while (it1 != s1.end() && it2 != s2.end())
	{
		str.push_back(*it1++);
		str.push_back(*it2++);
	}

	str.append(it1, s1.end());
	str.append(it2, s2.end());

	return str;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(str1_, str2_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(merge(str1_, str2_));
	}

private:
	std::string str1_;
	std::string str2_;
};

MAIN(CP)

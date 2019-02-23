/*********************************************************************
Extract maximum
---------------
URL: https://practice.geeksforgeeks.org/problems/extract-maximum/0

You have been given an alphanumeric string S, extract maximum numeric
value from that string. Alphabets will only be in lower case.

Input
-----
The first line contains a single integer T i.e. the number of test
cases. T testcases follow. The first and only line consists of
a String S.

Output
------
For each testcase, in a new line, print the maximum number extracted
from the string S.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <string>
#include <utility>

template<class It>
It search(It first, It last, It s_first, It s_last)
{
	auto start = first;
	auto s_start = s_first;

	while (first != last)
	{
		if (*first++ == *s_start)
		{
			if (++s_start == s_last)
				return start;
		}
		else
		{
			start = first;
			s_start = s_first;
		}
	}

	return last;
}

std::string::const_iterator strstr(const std::string& str, const std::string& sub)
{
	return search(str.begin(), str.end(), sub.begin(), sub.end());
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(str_, sub_str_);
	}

	virtual void solve(unsigned int) override
	{
		auto pos = strstr(str_, sub_str_);
		if (pos == str_.end())
			write_ln(-1);
		else
			write_ln(pos - str_.begin());
	}

private:
	std::string str_;
	std::string sub_str_;
};

MAIN(CP)

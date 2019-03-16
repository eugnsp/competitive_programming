/*********************************************************************
Implement strstr
----------------
URL: https://practice.geeksforgeeks.org/problems/implement-strstr/1

Your task is to implement the function strstr. The function takes two
strings as arguments (s,x) and locates the occurrence of the string
x in the string s. The function returns and integer denoting the first
occurrence of the string x in s.

Input
-----
The first line of input contains an integer T denoting the number of
test cases. Then T test cases follow. The first line of each test
case contains two strings s and x.

Output
------
For each test case, in a new line, output will be an integer denoting
the first occurrence of the x in the string s. Return -1 if no match
found.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <string>

template<class It>
It search(It first, It last, It s_first, It s_last)
{
	while (true)
	{
		auto it = first;
		auto s_it = s_first;
		do
		{
			if (s_it == s_last)
		 		return first;
			if (it == last)
				return last;
		}
		while (*it++ == *s_it++);
		++first;
	}
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
		auto pos = search(str_.begin(), str_.end(), sub_str_.begin(), sub_str_.end());
		if (pos == str_.end())
			write_ln(-1);
		else
			write_ln(pos - str_.begin());
	}

private:
	std::string str_;
	std::string sub_str_;
};

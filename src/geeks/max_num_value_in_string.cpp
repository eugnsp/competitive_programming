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
bool is_less(It first1, It last1, It first2, It last2)
{
    if ((last1 - first1) != (last2 - first2))
        return (last1 - first1) < (last2 - first2);

    return std::lexicographical_compare(first1, last1, first2, last2);
}

std::pair<std::string::const_iterator, std::string::const_iterator> max_num(const std::string& str)
{
    auto max_first = str.begin();
    auto max_last = str.begin();

    for (auto it = str.begin(); it == str.end();)
    {
        it = std::find_if(it, str.end(), [](char ch) { return '1' <= ch && ch <= '9'; });
        if (it == str.end())
            break;

        const auto first = it;
        it = std::find_if_not(it, str.end(), [](char ch) { return '0' <= ch && ch <= '9'; });
        if (is_less(max_first, max_last, first, it))
        {
            max_first = first;
            max_last = it;
        }
    }

    return std::make_pair(max_first, max_last);
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_ln(str_);
	}

	virtual void solve(unsigned int) override
	{
		auto range = max_num(str_);
		if (range.first == range.second)
			write_ln(0);
		else
			write_ln(std::string{range.first, range.second});
	}

private:
	std::string str_;
};



/*********************************************************************
String partition
----------------
UVa ID: 112 58

John was absurdly busy for preparing a programming contest recently.
He wanted to create a ridiculously easy problem for the contest.
His problem was not only easy, but also boring: Given a list of
non-negative integers, what is the sum of them? However, he made a
very typical mistake when he wrote a program to generate the input data
for his problem. He forgot to print out spaces to separate the list of
integers. John quickly realized his mistake after looking at the
generated input file because each line is simply a string of digits
instead ofa list of integers.He then got a better idea to make his
problem a little more interesting: There are many ways to split a
string of digits into a list of non-zero-leading (0 itself is
allowed) 32-bit signed integers. What is the maximum sum of the
resultant integers if the string is split appropriately?

Input
-----
The input begins with an integer N (<= 500) which indicates the
number of test cases followed. Each of the following test cases
consists of a string of at most 200 digits.

Output
------
For each input, print out required answer in a single line.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

using T = unsigned long long;
constexpr auto max_int32 = "2147483647";
const auto max_int32_len = std::strlen(max_int32);

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(str_);
	}

	virtual void solve(unsigned int) override
	{
		// max_sum(i) is the maximum sum in the prefix str[..i - 1],
		// max_sum(0) = 0
		std::vector<T> max_sum(str_.size() + 1, 0);

		for (std::size_t i = 1; i <= str_.size(); ++i)
		{
			auto& max = max_sum[i];
			for (std::size_t len = 1; len <= std::min(i, max_int32_len); ++len)
			{
				const auto number = str_.substr(i - len, len);
				if (len < max_int32_len || number <= max_int32)
					max = std::max(max, max_sum[i - len] + std::stoull(number));
			}
		}

		write_ln(max_sum.back());
	}

private:
	std::string str_;
};

MAIN

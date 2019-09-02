/*********************************************************************
Maximum numerical value in a string
-----------------------------------

Find the maximum numerical value in the given string.

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

	const auto is_19_digit = [](char ch) { return '1' <= ch && ch <= '9'; };
	const auto is_09_digit = [](char ch) { return '0' <= ch && ch <= '9'; };

	for (auto it = str.begin(); it == str.end();)
	{
		it = std::find_if(it, str.end(), is_19_digit);
		if (it == str.end())
			break;

		const auto first = it;
		it = std::find_if_not(it, str.end(), is_09_digit);
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
		if (range.first != range.second)
			write_ln(std::string{range.first, range.second});
		else
			write_ln(0);
	}

private:
	std::string str_;
};

MAIN

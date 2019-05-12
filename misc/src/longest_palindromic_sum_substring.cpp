/*********************************************************************
Longest palindromic sum substring
---------------------------------

In the given string of digits, find the length of the longest even-
length substring such that the sum of digits in its left half equals
the sum of digits in its right half.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <iterator>
#include <string>

unsigned int to_number(const char ch)
{
	assert('0' <= ch && ch <= '9');
	return static_cast<unsigned int>(ch - '0');
}

template<class It>
std::size_t longest_palindromic_sum_substr_length(const It first, const It last)
{
	if (first == last)
		return 0;

	std::size_t max_len = 0;
	for (auto mid = std::next(first); mid != last; ++mid)
	{
		auto it_l = std::make_reverse_iterator(mid);
		auto it_r = mid;
		for (unsigned int left_sum = 0, right_sum = 0; it_l != std::make_reverse_iterator(first) && it_r != last;
			 ++it_l, ++it_r)
		{
			left_sum += to_number(*it_l);
			right_sum += to_number(*it_r);
			if (left_sum == right_sum)
				max_len = std::max(max_len, 1 + static_cast<std::size_t>(it_r - mid));
		}
	}

	return max_len;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(str_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(2 * longest_palindromic_sum_substr_length(str_.begin(), str_.end()));
	}

private:
	std::string str_;
};

MAIN

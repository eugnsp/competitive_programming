/*********************************************************************
Longest distinct-character substring
------------------------------------

For the given string find length of the longest substring that
consists of distinct characters.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <string>
#include <type_traits>

template<class It>
std::size_t longest_distinct_char_substr_len(const It first, const It last)
{
	using T = typename std::make_unsigned<typename std::iterator_traits<It>::value_type>::type;

	assert(first <= last);
	if (last - first <= 1)
		return static_cast<std::size_t>(last - first);

	std::array<It, static_cast<T>(-1)> right_most_it;
	std::fill(right_most_it.begin(), right_most_it.end(), last);
	right_most_it[static_cast<T>(*first)] = first;

	std::size_t max_len = 1;
	for (auto left = first, right = std::next(left); right != last; ++right)
	{
		auto& s = right_most_it[static_cast<T>(*right)];
		if (s != last && left <= s)
			left = std::next(s);

		max_len = std::max(max_len, 1 + static_cast<std::size_t>(right - left));
		s = right;
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
		write_ln(longest_distinct_char_substr_len(str_.begin(), str_.end()));
	}

private:
	std::string str_;
};

MAIN

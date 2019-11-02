/*********************************************************************
Count anagram substrings
------------------------

For the given string and the pattern, find the number of occurrences
of the pattern and its permutations (anagrams) in the string.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <string>
#include <unordered_map>

std::size_t count_anagram_substrings(const std::string& string, const std::string& substring)
{
	assert(string.length() >= substring.length());

	std::unordered_map<char, std::ptrdiff_t> hash;
	std::size_t positive_count = substring.length();
	std::size_t negative_count = 0;

	const auto add = [&hash, &positive_count, &negative_count](char ch)
					 { (hash[ch]++ >= 0) ? ++positive_count : --negative_count; };
	const auto sub = [&hash, &positive_count, &negative_count](char ch)
					 { (hash[ch]-- > 0) ? --positive_count : ++negative_count; };

	for (auto ch : substring)
		++hash[ch];

	for (std::size_t i = 0; i < substring.length(); ++i)
		sub(string[i]);

	std::size_t count = (positive_count == 0 && negative_count == 0);
	for (std::size_t i = 0, i2 = substring.length(); i2 < string.length(); ++i, ++i2)
	{
		add(string[i]);
		sub(string[i2]);
		if (positive_count == 0 && negative_count == 0)
			++count;
	}

	return count;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(string_, substring_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(count_anagram_substrings(string_, substring_));
	}

private:
	std::string string_;
	std::string substring_;
};

MAIN

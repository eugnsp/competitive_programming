/*********************************************************************
Pesky palindromes
-----------------
UVa ID: 003 53

A palindrome is a sequence of one or more characters that reads the
same from the left as it does fromthe right. For example, Z, TOT and
MADAM are palindromes, but ADAM is not. Your job, should you choose
to accept it, is to write a program that reads a sequence of strings
and for each string determines the number of UNIQUE palindromes that
are substrings.

Input
-----
The input file consists of a number of strings (one per line), of
at most 80 characters each, starting incolumn 1.

Output
------
For each non-empty input line, the output consists of one line
containing the message:
	The string 'input  string' contains n palindromes.
where input string is replaced by the actual input string and n
is replaced by the number of UNIQUE palindromes that are substrings.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <string>
#include <unordered_set>
#include <vector>

class Polynomial_hash
{
public:
	template<class It>
	Polynomial_hash(It first, const It last)
	{
		const auto n = static_cast<std::size_t>(last - first);
		degrees_.reserve(n + 1);
		hashes_.reserve(n + 1);

		degrees_.push_back(1);
		hashes_.push_back(0);

		while (first != last)
		{
			degrees_.push_back(degrees_.back() * p);
			hashes_.push_back(hashes_.back() * p + *first++);
		}
	}

	std::size_t operator()(const std::size_t first, const std::size_t last) const
	{
		assert(first <= last);
		return hashes_[last] - hashes_[first] * degrees_[last - first];
	}

private:
	static constexpr std::size_t p = 257;

	std::vector<std::size_t> degrees_;
	std::vector<std::size_t> hashes_;
};

std::size_t count_unique_palindromes(const std::string& str)
{
	const auto n = str.length();
	if (n <= 1)
		return n;

	const Polynomial_hash hash(str.begin(), str.end());
	const Polynomial_hash rhash(str.rbegin(), str.rend());

	std::unordered_set<std::size_t> hashes;

	// Even length
	for (std::size_t center = 1; center < n; ++center)
		for (std::size_t len = 1; len <= std::min(center, n - center); ++len)
		{
			const auto first1 = center - len;
			const auto last1 = center + len;
			const auto first2 = n - last1;
			const auto last2 = n - first1;

			if (auto h = hash(first1, last1), rh = rhash(first2, last2); h == rh)
				hashes.insert(h);
		}

	// Odd length
	for (std::size_t center = 0; center < n; ++center)
		for (std::size_t len = 1; len <= std::min(center + 1, n - center); ++len)
		{
			const auto first1 = center + 1 - len;
			const auto last1 = center + len;
			const auto first2 = n - last1;
			const auto last2 = n - first1;

			if (auto h = hash(first1, last1), rh = rhash(first2, last2); h == rh)
				hashes.insert(h);
		}

	return hashes.size();
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_ln(s_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln("The string '", s_, "' contains ", count_unique_palindromes(s_), " palindromes.");
	}

private:
	std::string s_;
};

MAIN

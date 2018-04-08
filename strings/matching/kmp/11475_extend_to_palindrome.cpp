/*********************************************************************
Extend to palindrome
--------------------
UVa ID: 11475

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <string>
#include <vector>

// Returns the KMP table of longest prefixes that are proper suffixes
std::vector<std::size_t> lps_table(const std::string& s)
{
	const auto len = s.length();
	std::vector<std::size_t> lps(len);

	std::size_t lps_len = 0;
	lps[0] = lps_len;

	for (std::size_t i = 1; i < len; ++i)
	{
		while (lps_len > 0 && s[lps_len] != s[i])
			lps_len = lps[lps_len - 1];

		if (s[lps_len] == s[i])
			++lps_len;

		lps[i] = lps_len;
	}

	return lps;
}

std::string shortest_palindrome(const std::string& s)
{
	const std::string rs(s.rbegin(), s.rend());
	const auto lps = lps_table(rs);

	// Find the reversed string in the original one
	std::size_t lps_len = 0;
	for (std::size_t i = 0; i < s.length(); ++i)
	{
		while (lps_len > 0 && rs[lps_len] != s[i])
			lps_len = lps[lps_len - 1];

		if (rs[lps_len] == s[i])
			++lps_len;
	}

	assert(lps_len <= s.length());
	return s + rs.substr(lps_len);
}

class CP : public CP2
{
private:
	virtual bool read_input(std::istream& in) override
	{
		return std::getline(in, s_) && !s_.empty();
	}

	virtual void solve(std::ostream& out, unsigned int) const override
	{
		const auto p = shortest_palindrome(s_);
		assert(std::equal(p.begin(), p.end(), p.rbegin()));
		out << p << '\n';
	}

private:
	std::string s_;
};

int main()
{
	CP p;
	return p.run();
}

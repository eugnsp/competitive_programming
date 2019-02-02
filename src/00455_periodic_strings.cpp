/*********************************************************************
Periodic strings
----------------
UVa ID: 455

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cstddef>
#include <string>
#include <vector>

// Returns the KMP table of longest prefixes that are proper suffixes
auto lps_table(const std::string& s)
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

std::size_t shortest_period_length(const std::string& s)
{
	const auto len = s.length();

	const auto lps = lps_table(s);
	const auto period = len - lps.back();

	return (len % period == 0) ? period : len;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_ln(s_);
	}

	virtual void solve(unsigned int i_case) override
	{
		if (i_case > 0)
			write_ln();
		write_ln(shortest_period_length(s_));
	}

private:
	std::string s_;
};

MAIN(CP)

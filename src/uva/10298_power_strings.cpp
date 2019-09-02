/*********************************************************************
Power strings
-------------
UVa ID: 102 98

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

// Note: a better solution based on Knuth-Morris-Pratt algorithm
// exists, see problem UVa 00455 Periodic strings.

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <string>
#include <vector>

bool is_repetition(const std::string& s, std::size_t rep_count)
{
	assert(s.size() % rep_count == 0);
	const auto substr_length = s.size() / rep_count;

	for (std::size_t r = 1; r < rep_count; ++r)
		for (std::size_t i = 0; i < substr_length; ++i)
			if (s[i] != s[i + substr_length * r])
				return false;

	return true;
}

auto factorize(std::size_t n)
{
	std::vector<std::size_t> factors;
	for (std::size_t f = 1; f * f <= n; ++f)
		if (n % f == 0)
			factors.insert(factors.end(), {f, n / f});

	return factors;
}

std::size_t repetition_factor(const std::string& s)
{
	auto reps = factorize(s.size());
	std::sort(reps.rbegin(), reps.rend());

	std::size_t last_rep = 0;
	auto rep = reps.begin();
	while (rep != reps.end())
	{
		if (*rep != last_rep && is_repetition(s, *rep))
			return *rep;

		last_rep = *rep;
		++rep;
	}

	assert(false);
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_ln_non_empty(s_) && s_ != ".";
	}

	virtual void solve(unsigned int) override
	{
		write_ln(repetition_factor(s_));
	}

private:
	std::string s_;
};

MAIN


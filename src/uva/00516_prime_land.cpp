/*********************************************************************
Prime land
----------
UVa ID: 516

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "primes.hpp"
#include "util.hpp"
#include <cassert>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

class CP : public CP2
{
private:
	using T = unsigned int;

private:
	virtual bool read_input() override
	{
		std::string str;
		read_ln(str);
		if (str == "0")
			return false;

		std::istringstream number(str);

		factors_.clear();

		std::pair<T, unsigned int> f;
		while (number >> f.first && number >> f.second)
			factors_.push_back(f);

		return true;
	}

	virtual void solve(unsigned int) override
	{
		T number = 1;
		for (auto f : factors_)
			number *= power(f.first, f.second);

		assert(2 < number && number < 32767);
		const auto factors = factorize(number - 1);

		write(factors.back().first, ' ', factors.back().second);
		for (auto it = factors.rbegin() + 1; it != factors.rend(); ++it)
			write(' ', it->first, ' ', it->second);
		write_ln();
	}

private:
	std::vector<std::pair<T, unsigned int>> factors_;
};

MAIN

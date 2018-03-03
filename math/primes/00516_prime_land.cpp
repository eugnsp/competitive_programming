/*********************************************************************
Prime land
----------
UVa ID: 516

Goal:	find (x - 1) in the prime base representation.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "primes.hpp"
#include "util.hpp"
#include <cassert>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

class Prime_land : public CP2
{
private:
	using T = unsigned int;

private:
	virtual bool read_input(std::istream& in) override
	{
		// <base_1> <exp_1> ... <base_n> <exp_n>

		std::string str;
		std::getline(in, str);
		if (str == "0")
			return false;

		std::istringstream number(str);

		factors_.clear();

		std::pair<T, unsigned int> f;
		while (number >> f.first && number >> f.second)
			factors_.push_back(f);

		return true;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		T number = 1;
		for (auto f : factors_)
			number *= power(f.first, f.second);

		assert(2 < number && number < 32767);
		const auto factors = factorize(number - 1);

		out << factors.back().first << ' ' << factors.back().second;
		for (auto it = factors.rbegin() + 1; it != factors.rend(); ++it)
			out << ' ' << it->first << ' ' << it->second;
		out << '\n';
	}

	

private:
	std::vector<std::pair<T, unsigned int>> factors_;
};

int main()
{
	Prime_land p;
	return p.run();
}

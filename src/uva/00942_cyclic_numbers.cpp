/*********************************************************************
Cyclic numbers
--------------
UVa ID: 009 42

Given two positive integers, that represent a rational number as a
fraction, we want to produce thedecimal periodic representation of
the fraction's value. A decimal periodic representation has the
following form:
	d1...di.dj...dl(dm...dn)
where each dis a decimal digit and the inclusion of dm...dn between
parenthesis means that this sequence of digits is repeated forever.
We call (dm:::dn) the periodic part of the representation. As examples
of decimal periodic representations, consider for instance:
 	1/3 = 0.(3), 13/66 = 0.1(96), 170/12 = 14.1(6), 24/6 = 4.0
Notice that the periodic part is omitted if the decimal expansion of
the fraction is finite, as illustrated by the last example. All
fractions can be represented precisely, in a finite way, using this
kind of representation. However we cannot give an explicit bound for
the size of the periodic part (see for example the second fraction
in the sample input below).

Input
-----
The first line contains a non-negative integer n, which is the number
of fractions to convert to the decimal periodic representation. The
following n lines contain two positive integers, respectively the
numerator and the denominator of the fraction to be converted.

Output
------
For each fraction in the input, there must be a line in the output
containing its decimal periodic representation.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "util.hpp"
#include <cstddef>
#include <string>
#include <unordered_map>

std::string to_decimal(unsigned int num, unsigned int denom)
{
	std::string str;
	std::unordered_map<unsigned int, std::size_t> remainders;

	str += std::to_string(num / denom) + '.';
	auto pos = str.length();

	num %= denom;
	while (true)
	{
		remainders[num] = pos++;
		num *= 10;
		str.push_back(to_digit(num / denom));
		num %= denom;
		if (num == 0)
			break;

		if (const auto pos = remainders.find(num); pos != remainders.end())
		{
			str.insert(pos->second, 1, '(');
			str.push_back(')');
			break;
		}
	}

	return str;
}

using T = int;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(num_, denom_);
	}

	virtual void solve(unsigned int) override
	{
		const auto str = to_decimal(num_, denom_);
		write_ln(str);
	}

private:
	unsigned int num_;
	unsigned int denom_;
};

MAIN

/*********************************************************************
Parity
------
UVa ID: 109 31

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "bit.hpp"
#include <algorithm>
#include <string>
#include <utility>

std::pair<std::string, unsigned int> binary_and_parity(unsigned int i)
{
	std::string str;
	unsigned int parity = 0;

	while (i > 0)
	{
		if (is_bit_set<0>(i))
		{
			str.push_back('1');
			++parity;
		}
		else
			str.push_back('0');
		i >>= 1;
	}

	std::reverse(str.begin(), str.end());
	return {str, parity};
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(i_) && i_ > 0;
	}

	virtual void solve(unsigned int) override
	{
		const auto bp = binary_and_parity(i_);
		write_ln("The parity of ", bp.first, " is ", bp.second, " (mod 2).");
	}

private:
	unsigned int i_;
};

MAIN


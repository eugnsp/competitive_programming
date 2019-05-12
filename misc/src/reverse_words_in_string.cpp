/*********************************************************************
Reverse words in a string
-------------------------

Reverse all words in the given string.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <iterator>
#include <string>

template<class It, typename T>
void reverse_ranges(It first, const It last, const T& separator)
{
	while (true)
	{
		const auto sep = std::find(first, last, separator);
		std::reverse(first, sep);
		if (sep == last)
			break;
		first = std::next(sep);
	}
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_ln(str_);
	}

	virtual void solve(unsigned int) override
	{
		reverse_ranges(str_.begin(), str_.end(), '.');
		write_ln(str_);
	}

private:
	std::string str_;
};

MAIN

/*********************************************************************
Smallest number in a permutation
--------------------------------

For the given signature of permutations of the digits {0..9} find
the permutation that represents the smallest number. The signature
consists of letters "I" and "D". "I"/"D" indicates that the next digit
is larger/smaller than the previous one. For example, the permutation
"21436587" has the signature "DIDIDID".

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <algorithm>
#include <string>

template<typename T>
char to_digit(const T n)
{
	return static_cast<char>('0' + n);
}

std::string smallest_number(const std::string& signature)
{
	assert(signature.length() <= 8);
	auto n = signature.length() + 1;
	std::string num(n, ' ');

	auto digit = to_digit(n);
	auto last_digit = digit;

	auto it = signature.rbegin();
	while (n != 0)
	{
		if (it == signature.rend() || *it == 'I')
			for (auto ch = digit; ch <= last_digit; ++ch)
				num[--n] = ch;

		--digit;
		if (it != signature.rend() && *it++ == 'I')
			last_digit = digit;
	}

	return num;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(signature_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(smallest_number(signature_));
	}

private:
	std::string signature_;
};

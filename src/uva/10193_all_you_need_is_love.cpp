/*********************************************************************
All you need is love
--------------------
UVa ID: 101 93

There was invented a new powerfull gadget by the IBM corporation
called the love machine! Given a string made of binary digits, the
love machine answers if it's made only of love, that is, if all you
need is love to build that string. The definition of love for the love
machine is another string of binary digits, given by a human operator.
Let's say we have a string L which represents "love" and we give a
string S for the love machine. We say that all you need is love to
build S, if we can repeatly subtract L from S until we reach L. The
subtraction defined here is the same arithmetic subtraction in base 2.
By this definition it's easy to see that if L > S (in binary), then S
is not made of love. If S = L then S is obvious made of love. Your task
in this problem is: given two valid binary strings, S1 and S2, find if
it's possible to have a valid string L such that both S1 and S2 can be
made only of L (i.e. given two valid strings S1 and S2, find if there
exists at least one valid string L such as both S1 and S2 are made only
of L).

Input
-----
The first line of input is a positive integer N < 10'000 which stands
for the number of test cases. Then, 2N lines will follow. Each pair of
lines consists in one test case. Each line of the pair stands for each
string (S1 and S2) to be entered as an input for the love machine. No
string will have more than 30 characters. You can assume that all
strings in the input will be valid according to the rules above.

Output
------
For each string pair, you must print one of the following messages:
	Pair #p: All you need is love!
	Pair #p: Love is not all you need!
Where p stands for the pair number (starting from 1). You should print
the first message if there exists at least one valid string L such as
both S1 and S2 can be made only of L. Otherwise, print the second line.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <string>

template<typename T>
T exchange(T& x, T new_x)
{
	const auto old_x = x;
	x = new_x;
	return old_x;
}

template<typename T>
T gcd(T x, T y)
{
	while (x != 0)
		y = exchange(x, y % x);
	return y;
}

template<typename T = unsigned int>
T bin_str_to_uint(const std::string& str)
{
	auto n = static_cast<T>(0);
	for (auto it = str.begin(); it != str.end(); ++it)
	{
		n <<= 1;
		n |= (*it == '0' ? 0 : 1);
	}

	return n;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(s1_, s2_);
	}

	virtual void solve(unsigned int i_case) override
	{
		const auto n1 = bin_str_to_uint(s1_);
		const auto n2 = bin_str_to_uint(s2_);

		write_ln("Pair #", i_case, ": ",
			gcd(n1, n2) > 1 ? "All you need is love!" : "Love is not all you need!");
	}

private:
	std::string s1_, s2_;
};

MAIN

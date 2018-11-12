/*********************************************************************
How many zeros and how many digits
----------------------------------
UVa ID: 100 61

Given a decimal integer number you will have to find out how many 
trailing zeros will be there in its factorial in a given number system
and also you will have to find how many digits will its factorial have
in a given number system. You can assume that for a B-based number 
system there are B different symbols to denote values ranging from 
0 to B-1.

Input
-----
There will be several lines of input. Each line makes a block. Each
line will contain a decimal number N (a 20-bit unsigned number) and a
decimal number B (1 < B <= 800), which is the base of the number
system you have to consider. As for example, 5! = 120 (in decimal) 
but it is 78 in hexadecimal number system. So in hexadecimal 5! has
no trailing zeros.

Output
------
For each line of input output in a single line how many trailing zeros
will the factorial of that number have in the given number system and 
also how many digits will the factorial of that number have in that 
given number system. Separate these two numbers with a single space.
You can be sure that the number of trailing zeros or the number of 
digits will not be greater than 2^31 - 1.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>

using N = unsigned int;
using Exp = unsigned int;

Exp remove_factor(N& n, N factor)
{
	assert(n % factor == 0);
	Exp exp = 0;
	do
	{
		n /= factor;
		++exp;
	}
	while (n % factor == 0);
	return exp;
}

// Returns the prime factors in (n) and their exponents
std::vector<std::pair<N, Exp>> prime_factors(N n)
{
	assert(1 < n && n <= 800);
	constexpr N primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
		37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83,	89, 97, 101,
		103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163,
		167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229,
		233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293,
		307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373,
		379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443,
		449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521,
		523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601,
		607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673,
		677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757,
		761, 769, 773, 787, 797};

	std::vector<std::pair<N, Exp>> factors;
	for (N p : primes)
	{
		if (p * p > n)
			break;

		if (n % p == 0)
		{
			const auto exp = remove_factor(n, p);
			factors.push_back({p, exp});
		}
	}

	if (n != 1)
		factors.push_back({n, 1});

	return factors;
}

// Returns the number of trailing zeros in (n!)
// in the number system with given (base)
Exp n_trailing_zeros(N n, N base)
{
	assert(base > 1);
	if (n <= 1)
		return 0;

	const auto factors = prime_factors(base);
	std::vector<Exp> exps(factors.size(), 0);

	for (N f = 0; f < factors.size(); ++f)
	{
		N i = 1;
		while ((i *= factors[f].first) <= n)
			exps[f] += n / i;
		exps[f] /= factors[f].second;
	}

	return *std::min_element(exps.begin(), exps.end());
}

// Returns the number of digits in (n!)
// in the number system with given (base)
Exp n_digits(N n, N base)
{
	const auto safety = 1e-7;	// In case lgamma(n + 1) = log(base)
	const auto nd = std::lgamma(n + 1) / std::log(base);
	return static_cast<Exp>(nd + safety) + 1;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(n_, base_);
	}

	virtual void solve(unsigned int) override
	{
		Exp nz = n_trailing_zeros(n_, base_);
		Exp nd = n_digits(n_, base_);
		write_ln(nz, ' ', nd);
	}

private:
	N n_;
	N base_;
};

MAIN(CP)

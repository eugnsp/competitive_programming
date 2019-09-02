/*********************************************************************
Odd root sum
------------
UVa ID: 112 60

Given the value of an n you will have to find the modulo 100'000'000
value of the following expression:
	⌊sqrt(1)⌋ + ⌊sqrt(3)⌋ + ⌊sqrt(5)⌋ + ... + ⌊sqrt(m)⌋,
where m is the largest odd number not greater than n. In other words,
you will have to find the value of S where
	S = (⌊sqrt(1)⌋ + ⌊sqrt(3)⌋ + ... + ⌊sqrt(m)⌋) mod 100'000'000.

Input
-----
The input file contains at most 30'000 lines of inputs. Each line
contains a single 64-nit signed integer which denotes the value of n.
Input is terminated by a line containing a single zero which should
not be processed.

Output
------
For each line of input produce one line of output. This line contains
the value of S.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"

constexpr unsigned long long mod = 100'000'000;
constexpr unsigned long long inv3 = 66'666'667;
static_assert((3 * inv3) % mod == 1);

template<typename T>
T floor_sqrt(const T x)
{
	T left = 0;
	T right = static_cast<T>(1) << (4 * sizeof(x));

	// left ^ 2 <= x, (right + 1) ^ 2 > x
	// At the beginning: left = 0, right = x
	// At the end: left = right = floor(sqrt(x))

	while (left != right)
	{
		auto mid = (left + right + 1) / 2;
		if (mid * mid <= x)
			left = mid;
		else
			right = mid - 1;
	}

	return left;
}

template<typename T>
T add(const T x, const T y)
{
	return (x + y) % mod;
}

template<typename T>
T mul(const T x, const T y)
{
	return ((x % mod) * (y % mod)) % mod;
}

template<typename T>
T mul(const T x, const T y, const T z)
{
	return (mul(x, y) * z) % mod;
}

template<typename T>
T sum_odd_sqrt(const T n)
{
	const auto sqrt = floor_sqrt(n);
	const auto m = (sqrt - 1) / 2;

	// (1 + 2) x 2 + (3 + 4) x 4 + (5 + 6) x 6 + ...
	auto sum = mul(m * (m + 1), (8 * m + 1), inv3);
	if (sqrt % 2 == 0)
		sum = add(sum, mul(sqrt, sqrt - 1));

	const auto res = mul(sqrt, (n + 1) / 2 - sqrt * sqrt / 2);
	return add(sum, res);
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(n_) && n_ > 0;
	}

	virtual void solve(unsigned int) override
	{
		write_ln(sum_odd_sqrt(n_));
	}

private:
	unsigned long long n_;
};

MAIN


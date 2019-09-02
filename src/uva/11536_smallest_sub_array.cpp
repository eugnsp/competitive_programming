/*********************************************************************
Smallest sub-array
------------------
UVa ID: 115 36

Consider an integer sequence consisting of N elements where
	X1 = 1,
	X2 = 2,
	X3 = 3,
	Xi = (X{i-1} + X{i-2} + X{i-3}) % M + 1 for i= 4 to N.
Find the smallest subsequence from the given sequence that contains
all the integers from 1 to K.

Input
-----
First line of input is an integer T (T < 100) that represents the
number of test cases. Each case consists of a line containing 3
integers N (2 < N < 1'000'001), M (0 < M < 1001) and K (1 < K < 101).
The meaning of these variables is mentioned above.

Output
------
For each case, output the case number followed by the minimum
length of the subsequence. If there is no valid subsequence,
output "sequence nai" instead. Look at the sample for exact format.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <optional>
#include <vector>

template<typename T>
class Xi
{
public:
	Xi(T m) : m_(m)
	{}

	const T& operator*() const
	{
		return xi_;
	}

	void operator++()
	{
		const auto xip3 = (xi_ + xip1_ + xip2_ + 3) % m_;
		xi_ = std::exchange(xip1_, std::exchange(xip2_, xip3));
	}

private:
	const T m_;

	T xi_ = 0;
	T xip1_ = 1;
	T xip2_ = 2;
};

template<typename T>
std::optional<std::size_t> smallest_windows_size(std::size_t n, T m, T k)
{
	std::optional<std::size_t> min_len;
	std::size_t l = 0, r = 0;
	Xi<T> xi_l(m), xi_r(m);

	std::vector<std::size_t> counter(k, 0);
	T count = 0;

	while (true)
		if (count == k)
		{
			min_len = (min_len ? std::min(*min_len, r - l) : r - l);

			if (*xi_l < k && counter[*xi_l] > 0)
			{
				--counter[*xi_l];
				if (counter[*xi_l] == 0)
					--count;
			}
			++xi_l, ++l;
		}
		else
		{
			if (r < n)
			{
				if (*xi_r < k)
				{
					++counter[*xi_r];
					if (counter[*xi_r] == 1)
						++count;
				}
				++xi_r, ++r;
			}
			else
				break;
		}

	return {min_len};
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(n_, m_, k_);
	}

	virtual void solve(unsigned int i_case) override
	{
		write("Case ", i_case, ": ");

		if (auto len = smallest_windows_size(n_, m_, k_); len)
			write_ln(*len);
		else
			write_ln("sequence nai");
	}

private:
	std::size_t n_, m_, k_;
};

MAIN


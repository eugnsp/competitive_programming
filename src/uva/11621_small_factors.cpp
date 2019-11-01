/*********************************************************************
Small factors
-------------
UVa ID: 116 21

... An alternative that substantially reduces this upper bound is
using a mixed Radix-2/3 FFT algorithm. In this case, the number of
samples to be transformed should be expressed as a product of prime
factors 2 and 3:
	C_{2, 3} = {n = 2^i 3^j such that i, j belong to N}.
Given a positive integer number m, find the smallest number n in the
set C_{2, 3}, as defined above, such that n >= m. We will denote this
number as n = Next_{2, 3}(m).

Input
-----
The input consists of a sequence of positive integer numbers, m,
one number per line. The end of the input is marked by a value m = 0.
No input numberm shall be greater than 2^31.

Output
------
For each non-zero input value m, the program is to write one line with
the value of Next_{2, 3}(m), as defined above. No trailing/leading
blank spaces should be written after/before any output number.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <cmath>
#include <limits>

template<typename T>
T next_pow_2_3(T m)
{
	auto n = std::numeric_limits<T>::max();

	const auto log2_m = std::log2(m);
	const auto log2_3 = std::log2(3);

	auto pow3 = T{1};
	unsigned int exp3 = 0;

	while (true)
		if (pow3 < m)
		{
			const auto exp2 = static_cast<unsigned int>(std::floor(log2_m - exp3 * log2_3));
			auto n1 = pow3 * (T{1} << exp2);
			if (n1 < m)
				n1 *= 2;
			assert(n1 >= m);
			n = std::min(n, n1);
			++exp3, pow3 *= 3;
		}
		else
			return std::min(n, pow3);
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(m_) && m_ > 0;
	}

	virtual void solve(unsigned int) override
	{
		write_ln(next_pow_2_3(m_));
	}

private:
	unsigned long m_;
};

MAIN

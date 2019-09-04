/*********************************************************************
Shift-and-subtract division
---------------------------
Chapter 2, problem 8

Implement shift-and-subtract division algorithm for unsigned integers.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include <cassert>
#include <climits>
#include <type_traits>
#include <utility>

// Returns {num / denom, num % denom}
template<class T>
std::pair<T, T> uint_div(T num, const T denom)
{
	static_assert(std::is_unsigned_v<T>);
	assert(denom != 0);

	constexpr T msb = T{1} << (CHAR_BIT * sizeof(T) - 1);

	T quotient = 0;
	T remainder = 0;

	auto n_bits = CHAR_BIT * sizeof(T);
	while (n_bits-- > 0)
	{
		remainder <<= 1;
		if (num & msb)
			remainder |= 1;

		num <<= 1;
		quotient <<= 1;
		if (remainder >= denom)
		{
			remainder -= denom;
			quotient |= 1;
		}
	}

	return {quotient, remainder};
}

int main()
{
	for (unsigned int num = 0; num < 1'000; ++num)
		for (unsigned int denom = 1; denom < 1'000; ++denom)
		{
			auto r = uint_div(num, denom);
			assert(r.first == num / denom);
			assert(r.second == num % denom);
		}

	constexpr unsigned int max = -1;
	for (unsigned int num = max; num > max - 1'000; --num)
		for (unsigned int denom = max; denom > max - 1'000; --denom)
		{
			auto r = uint_div(num, denom);
			assert(r.first == num / denom);
			assert(r.second == num % denom);
		}

	return 0;
}

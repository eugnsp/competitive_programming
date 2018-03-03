// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <utility>

template<typename T>
T power(T base, unsigned int exp)
{
	T r = 1;
	while (exp > 0)
	{
		if (exp & 1u)
			r *= base;
		base *= base;
		exp >>= 1;
	}

	return r;
}

template<typename T>
T exchange(T& value, T&& new_value)
{
	auto old_value = std::move(value);
	value = std::forward<T>(new_value);
	return old_value;
}

template<typename T>
T gcd(T x, T y)
{
	while (y != 0)
		x = exchange(y, x % y);

	return x;
}

template<typename T>
bool between(T value, T x, T y)
{
	if (x < y)
		return x <= value && value <= y;
	else
		return y <= value && value <= x;
}

template<typename T>
void sort2(T& x, T& y)
{
	if (y < x)
		std::swap(x, y);
}

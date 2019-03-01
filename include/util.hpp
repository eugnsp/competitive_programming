// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <utility>

template<typename T>
struct Identity
{
	using Type = T;
};

// Replaces (value) with (new_value) and returns the old value
template<typename T, typename U>
T exchange(T& value, U&& new_value)
{
	auto old_value = std::move(value);
	value = std::forward<U>(new_value);
	return old_value;
}

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
T gcd(T x, T y)
{
	while (y != 0)
		x = exchange(y, x % y);

	return x;
}

template<typename T>
bool between(T value, typename Identity<T>::Type x, typename Identity<T>::Type y)
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

// Returns the absolute value of the difference (x - y)
template<typename T>
T abs_diff(T x, T y)
{
	return y > x ? y - x : x - y;
}

template<typename T>
std::pair<T, T> minmax(T x, T y)
{
	using P = std::pair<T, T>;
	return (y < x) ? P{y, x} : P{x, y};
}

template<typename T>
char to_ucase_letter(T x)
{
	return static_cast<char>('A' + x);
}

template<typename T>
char to_digit(T x)
{
	return static_cast<char>('0' + x);
}

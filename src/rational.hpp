// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <cassert>
#include <cmath>
#include <utility>

template<typename T>
class Rational
{
public:
	Rational() = default;

	Rational(T numerator, T denominator = 1)
	{
		numerator_ = numerator;
		denominator_ = denominator;
		reduce();
	}

	T numerator() const
	{
		return numerator_;
	}

	T denominator() const
	{
		return denominator_;
	}

	bool is_zero() const
	{
		return numerator_ == 0;
	}

private:
	static T exchange(T& value, T new_value)
	{
		auto old_value = value;
		value = new_value;
		return old_value;
	}

	static T gcd(T x, T y)
	{

		// x = std::abs(x);
		// y = std::abs(y);

		while (y != 0)
			x = exchange(y, x % y);
		return x;
	}

	void reduce()
	{
		const auto d = gcd(numerator_, denominator_);
		numerator_ /= d;
		denominator_ /= d;
	}

private:
	T numerator_;
	T denominator_;
};

template<typename T>
class Rational_hash
{
public:
	std::size_t operator()(const Rational<T>& r) const
	{
		std::hash<T> h;
		auto h1 = h(r.numerator());
		auto h2 = h(r.denominator());
		return h1 ^ h2;
	}
};

template<typename T>
bool operator<(const Rational<T>& r1, const Rational<T>& r2)
{
	if (r1.numerator() != r2.numerator())
		return r1.numerator() < r2.numerator();
	return r1.denominator() < r2.denominator();
}

template<typename T>
bool operator==(const Rational<T>& r1, const Rational<T>& r2)
{
	return r1.numerator() == r2.numerator() && r1.denominator() == r2.denominator();
}

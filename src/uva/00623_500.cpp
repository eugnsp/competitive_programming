/*********************************************************************
500!
----
UVa ID: 006 23

Considering the fact that 500! gives 1135-digit number. No standard,
neither integer nor floating, data type is applicable here. Your task
is to write a programs which calculates a factorial of a given number.

Input
-----
Any number of lines, each containing value n (n <= 1000) for which you
should provide value of n!.

Output
------
2 lines for each input case. First should contain value n followed by
character "!"". The second should contain calculated value n!.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstdint>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

char to_digit(unsigned char n)
{
	assert(n <= 9);
	return static_cast<char>('0' + n);
}

class Big_uint
{
public:
	template<typename T>
	explicit Big_uint(const T value)
	{
		assign(value);
	}

	template<typename T>
	void operator*=(T factor)
	{
		assert(factor != 0);

		T carry = 0;
		for (auto& digit : data_)
		{
			const auto add = factor * digit + carry;
			digit = add % 10;
			carry = add / 10;
		}

		while (carry != 0)
			data_.push_back(std::exchange(carry, carry / 10) % 10);
	}

	std::string to_string() const
	{
		std::string str;
		str.reserve(data_.size());
		std::transform(data_.rbegin(), data_.rend(), std::back_inserter(str), to_digit);
		return str;
	}

private:
	template<typename T>
	void assign(T value)
	{
		data_.clear();
		do
			data_.push_back(std::exchange(value, value / 10) % 10);
		while (value != 0);
	}

private:
	std::vector<unsigned char> data_;
};

Big_uint factorial(unsigned int n)
{
	constexpr auto max_factor = static_cast<std::uintmax_t>(-1) / 10;

	Big_uint factorial{1};
	for (unsigned int i = 2; i <= n;)
	{
		std::uintmax_t factor = 1;
		do
			factor *= i++;
		while (i <= n && factor < max_factor / i);
		factorial *= factor;
	}

	return factorial;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(n_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(n_, '!');
		write_ln(factorial(n_).to_string());
	}

private:
	unsigned int n_;
};

MAIN

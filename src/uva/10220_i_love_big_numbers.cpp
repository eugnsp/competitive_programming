/*********************************************************************
I love big numbers!
-------------------
UVa ID: 102 20

A Japanese young girl went to a Science Fair at Tokyo. There she met
with a Robot named Mico-12, which had AI. The Japanese girl thought,
she can do some fun with that Robot. She asked her, "Do you have any
idea about maths?". "Yes! I love mathematics", The Robot replied.
"Okey! Then I am giving you a number, you have to find out the
factorial of that number. Then find the sum of the digits of your
result!. Suppose the number is 5. You first calculate 5! = 120, then
find sum of the digits 1 + 2 + 0 = 3. Can you do it?". "Yes. I can
do!" Robot replied. "Suppose the number is 100, what will be the
result?". At this point the Robot started thinking and calculating.
After a few minutes the Robot head burned out and it cried out loudly
"Time Limit Exceeds". The girl laughed at the Robot and said "The sum
is definitely 648". "How can you tell that?" Robot asked the girl.
"Because I am an ACM World Finalist and I can solve the Big Number
problems easily". Saying this, the girl closed her laptop computer
and went away. Now, your task is to help the Robot with the similar
problem.

Input
-----
The input file will contain one or more test cases. Each test case
consists of one line containing an integers n (n <= 1000).

Output
------
For each test case, print one line containing the required number.
This number will always fit into an integer, i.e. it will be less than
2^31 - 1.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <numeric>
#include <vector>
#include <utility>

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
		for (std::size_t i = 0; i < data_.size(); ++i)
		{
			const auto add = factor * data_[i] + carry;
			data_[i] = add % 10;
			carry = add / 10;
		}

		while (carry != 0)
			data_.push_back(std::exchange(carry, carry / 10) % 10);
	}

	template<typename T>
	T digits_sum() const
	{
		return std::accumulate(data_.begin(), data_.end(), static_cast<T>(0));
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

unsigned int factorial_digits_sum(unsigned int n)
{
	Big_uint fact{1};
	for (unsigned int i = 2; i <= n; ++i)
		fact *= i;

	return fact.digits_sum<unsigned int>();
}

using T = int;

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(n_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(factorial_digits_sum(n_));
	}

private:
	unsigned int n_;
};

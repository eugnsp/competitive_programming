/*********************************************************************
Maximum sub-sequence product
----------------------------
UVa ID: 007 87

Bob needs money, and since he knows you are here, he decided to gamble
intelligently. The game is rather simple: each player gets a sequence
of integers. The players must determine, by using their mega-pocket
computers, which is the maximum product value which can be computed
with non empty sub-sequences of consecutive numbers from the given
sequence. The winner is the one which gets first the right result.
Can you help Bob with a program to compute quickly the wanted product,
particularly when the sequence is quite long?

Input
-----
The input file contains sequences of numbers. Each number will have at
most 5 digits. There will be atmost 100 numbers in each sequence. Each
sequence starts on a new line and may continue on several subsequent
lines. Each sequence ends with the number -999'999, which is not part
of the sequence.

Output
------
The maximum sub-sequence product for each sequence must be written on
the standard output, on a different line.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

constexpr auto stop_sig = -999'999;

char to_digit(unsigned char n)
{
	assert(n <= 9);
	return static_cast<char>('0' + n);
}

class Big_int
{
public:
	template<typename T>
	explicit Big_int(const T value)
	{
		assign(value);
	}

	template<typename T>
	Big_int& operator=(const T value)
	{
		assign(value);
		return *this;
	}

	template<typename T>
	void operator*=(T factor)
	{
		assert(factor != 0);
		if (factor < 0)
		{
			factor = -factor;
			is_negative_ = !is_negative_;
		}

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

	bool operator<(const Big_int& other) const
	{
		if (is_negative_ != other.is_negative_)
			return is_negative_;
		if (data_.size() != other.data_.size())
			return data_.size() < other.data_.size();

		for (std::size_t i = data_.size(); i > 0; --i)
			if (data_[i - 1] != other.data_[i - 1])
				return (data_[i - 1] < other.data_[i - 1]) != is_negative_;
		return false;
	}

	bool is_negative() const
	{
		return is_negative_;
	}

	std::string to_string() const
	{
		std::string str;
		if (is_negative_)
			str.push_back('-');
		str.reserve(str.size() + data_.size());
		std::transform(data_.rbegin(), data_.rend(), std::back_inserter(str), to_digit);
		return str;
	}

private:
	template<typename T>
	void assign(T value)
	{
		is_negative_ = (value < 0);
		if (value < 0)
			value = -value;

		data_.clear();
		do
			data_.push_back(std::exchange(value, value / 10) % 10);
		while (value != 0);
	}

private:
	bool is_negative_;
	std::vector<unsigned char> data_;
};

template<class It, typename T = typename std::iterator_traits<It>::value_type>
Big_int max_product(const It first, const It last)
{
	assert(first != last);

	Big_int left_prod{1};
	Big_int right_prod{1};
	Big_int max{*first};

	for (auto it = first; it != last; ++it)
		if (*it != 0)
		{
			left_prod *= *it;
			max = std::max(max, left_prod);
		}
		else
		{
			left_prod = 1;
			if (max.is_negative())
				max = 0;
		}

	for (auto it = std::make_reverse_iterator(last); it != std::make_reverse_iterator(first); ++it)
		if (*it != 0)
		{
			right_prod *= *it;
			max = std::max(max, right_prod);
		}
		else
		{
			right_prod = 1;
			if (max.is_negative())
				max = 0;
		}

	return max;
}

using T = int;

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		seq_.clear();

		T value;
		while (read(value) && value != stop_sig)
			seq_.push_back(value);

		return !seq_.empty();
	}

	virtual void solve(unsigned int) override
	{
		const auto max = max_product(seq_.begin(), seq_.end());
		write_ln(max.to_string());
	}

private:
	std::vector<int> seq_;
};

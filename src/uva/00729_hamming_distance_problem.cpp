/*********************************************************************
The Hamming distance problem
----------------------------
UVa ID: 007 29

The Hamming distance between two strings of bits (binary integers)
is the number of corresponding bit positions that differ. This can be
found by using XOR on corresponding bits or equivalently, by adding
corresponding bits (base 2) without a carry.

Input
-----
Input consists of several datasets. The first line of the input
contains the number of datasets, and it's followed by a blank line.
Each dataset contains N, the length of the bit strings and H, the
Hamming distance, on the same line. There is a blank line between
test cases.

Output
------
For each dataset print a list of all possible bit strings of length N
that are Hamming distance H from the bit string containing all 0s. That
is, all bit strings of length N with exactly H 1s printed in ascending
lexicographical order. The number of such bit strings is equal to
the combinatorial symbol C(N, H). This is the number of possible
combinations of N - H zeros and H ones. This number can be very large.
The program should work for 1 <= H <= N <= 16. Print a blank line
between datasets.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <string>

class Hamming_distance_strings
{
public:
	Hamming_distance_strings(std::size_t string_length, std::size_t hamming_dist) :
		length_(string_length), n_zeros_(string_length - hamming_dist)
	{
		assert(hamming_dist <= string_length);
	}

	// Calls the given function for all binary strings with
	// the given number of 1s in the lexicographic order
	template<class Fn>
	void for_each(Fn&& fn) const
	{
		std::string all_1s_string(length_, '1');
		get_next(fn, all_1s_string, 0);
	}

private:
	template<class Fn>
	void get_next(Fn&& fn, std::string& string, std::size_t pos) const
	{
		if (has_enough_zeros(string))
			fn(string);
		else
			for (std::size_t i = pos; i < length_; ++i)
			{
				string[i] = '0';
				get_next(fn, string, i + 1);
				string[i] = '1';
			}
	}

	bool has_enough_zeros(const std::string& string) const
	{
		const auto n = static_cast<std::size_t>(std::count(string.begin(), string.end(), '0'));
		return n == n_zeros_;
	}

private:
	const std::size_t length_;
	const std::size_t n_zeros_;
};

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(string_length_, hamming_dist_);
		assert(hamming_dist_ <= string_length_ && string_length_ <= 16);
	}

	virtual void solve(unsigned int i_case) override
	{
		if (i_case > 1)
			write_ln();

		const Hamming_distance_strings hds(string_length_, hamming_dist_);
		hds.for_each([](const std::string& str) { write_ln(str); });
	}

private:
	std::size_t string_length_;
	std::size_t hamming_dist_;
};

MAIN

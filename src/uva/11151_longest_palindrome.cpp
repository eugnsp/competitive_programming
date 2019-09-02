/*********************************************************************
Longest palindrome
------------------
UVa ID: 111 51

A palindrome is a string that reads the same from the left as it does
from the right. For example, I, GAG and MADAM are palindromes, but
ADAM is not. Here, we consider also the empty string as a palindrome.
From any non-palindromic string, you can always take away some letters,
and get a palindromic subsequence. For example, given the string ADAM,
you remove the letter M and get a palindrome ADA. Write a program
to determine the length of the longest palindrome you can get from
a string.

Input
-----

The first line of input contains an integer T (<= 60). Each of
the next T lines is a string, whose length is always less than 1'000.

Output
------
For each input string, your program should print the length of the
longest palindrome you can get by removing zero or more characters
from it.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cstddef>
#include <cstring>

std::size_t max_length_palindrome_remove(const std::string& str)
{
	const auto n = str.length();
	if (n <= 1)
		return n;

	Matrix<std::size_t> max_len(n, n);

	for (std::size_t i = 0; i < n; ++i)
		max_len(i, i) = 1;
	for (std::size_t i = 0; i < n - 1; ++i)
	{
		const auto left = i;
		const auto right = i + 1;
		max_len(left, right) = (str[left] == str[right]) ? 2 : 1;
	}

	// Loop pattern:
	// xx146
	//  xx25
	//   xx3
	for (std::size_t diag = 0; diag < n - 2; ++diag)
		for (std::size_t left = 0; left < n - 2 - diag; ++left)
		{
			const auto right = 2 + diag + left;
			if (str[left] == str[right])
				max_len(left, right) = 2 + max_len(left + 1, right - 1);
			else
				max_len(left, right) = std::max(max_len(left + 1, right), max_len(left, right - 1));
		}

	return max_len(0, n - 1);
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_ln(s_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(max_length_palindrome_remove(s_));
	}

private:
	std::string s_;
};

MAIN

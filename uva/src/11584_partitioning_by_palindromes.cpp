/*********************************************************************
Partitioning by palindromes
---------------------------
UVa ID: 115 84

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(string_);
	}

	virtual void solve(unsigned int) override
	{
		compute_palindromes_matrix();

		/*********************************************************************
		mp[i] is the minimum number of palindromic groups in
			the substring (string[0, i]).

		The recurrence relation is:
			mp[i] = 1 if (string[0, i]) is a palindrome,
				  = min {j <= i, string[j, i] is a palindrome} (mp[j - 1] + 1)
						otherwise.
		**********************************************************************/

		std::vector<std::size_t> mp(string_.length(), static_cast<std::size_t>(-1));

		for (std::size_t end = 0; end < string_.length(); ++end)
			if (palindromes_(0, end))
				mp[end] = 1;
			else
				for (std::size_t start = 1; start <= end; ++start)
					if (palindromes_(start, end))
						mp[end] = std::min(mp[end], mp[start - 1] + 1);

		write_ln(mp.back());
	}

	void compute_palindromes_matrix()
	{
		// Note: this DP algorithm is not the best

		/*********************************************************************
		p(i, j) is true iff the substring (string[i, j]) is a palindrome.

		The recurrence relation:
		p(i, j) = p(i + 1, j - 1) if string[i] == string[j]

		The base case:
		p(i, i) = true for all (i),
		p(i, i + 1) = (string[i] == string[i + 1]).
		**********************************************************************/

		const auto len = string_.length();
		palindromes_.resize_and_fill(len, len, false);

		for (std::size_t i = 0; i < len; ++i)
			palindromes_(i, i) = true;
		for (std::size_t i = 1; i < len; ++i)
			palindromes_(i - 1, i) = (string_[i - 1] == string_[i]);

		for (std::size_t end = 2; end < len; ++end)
			for (std::size_t start = 0; start < end - 1; ++start)
				if (string_[start] == string_[end] && palindromes_(start + 1, end - 1))
					palindromes_(start, end) = true;
	}

private:
	std::string string_;
	Matrix<bool> palindromes_;
};



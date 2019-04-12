/*********************************************************************
Number string
-------------
UVa ID: 016 50

The signature of a permutation is a string that is computed as follows:
for each pair of consecutive elements of the permutation, write down
the letter 'I' (increasing) if the second element is greater than the
first one, otherwise write down the letter 'D' (decreasing). For
example, the signature of the permutation {3, 1, 2, 7, 4, 6, 5} is
'DIIDID'. Your task is as follows: You are given a string describing
the signature of many possible permutations, find out how many
permutations satisfy this signature.

Input
-----
Each test case consists of a string of 1 to 1000 characters long,
containing only the letters 'I', 'D' or '?', representing a permutation
signature. Each test case occupies exactly one single line, without
leading or trailing spaces. Proceed to the end of file. The '?' in
these strings can be either 'I' or 'D'.

Output
------
For each test case, print the number of permutations satisfying the
signature on a single line. In case the result is too large, print the
remainder modulo 1'000'000'007.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cstddef>
#include <string>
#include <vector>

constexpr auto mod = 1'000'000'007u;

template<typename T>
T add(T x, T y)
{
	const auto r = x + y;
	return r < mod ? r : r - mod;
}

template<typename T>
T sub(T x, T y)
{
	return x > y ? x - y : x + mod - y;
}

unsigned int count_permutations(const std::string& signature)
{
	const auto n = signature.length() + 1;

	// count(len, first) is the number of permutations
	// of length (len + 1) beginning with the element (first),
	// part_sum(len, first) is the partial sum of the (len)-th row;
	// only (len - 1)-th row is needed to compute the next one

	std::vector<unsigned int> part_sum(n + 1, 0);
	std::vector<unsigned int> part_sum_prev(n + 1, 0);

	part_sum_prev[1] = 1;
	for (std::size_t len = 1; len < n; ++len)
	{
		for (std::size_t first = 0; first <= len; ++first)
			switch (signature[len - 1])
			{
			case 'D':
				part_sum[first + 1] = add(part_sum[first],
					sub(part_sum_prev[len], part_sum_prev[first]));
				break;

			case 'I':
				part_sum[first + 1] = add(part_sum[first], part_sum_prev[first]);
				break;

			default:
				part_sum[first + 1] = add(part_sum[first], part_sum_prev[len]);
			}
		std::swap(part_sum, part_sum_prev);
	}

	return part_sum_prev.back();
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(signature_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(count_permutations(signature_));
	}

private:
	std::string signature_;
};



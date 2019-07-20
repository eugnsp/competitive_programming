/*********************************************************************
Largest number with k swaps
---------------------------

For the string of digits representing a positive integer, and the
given number k, find the largest number that can be formed by
performing at most k swaps of digits.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <string>

template<class It>
std::string largest_number(It first, It last, std::size_t n_swaps)
{
	if (last - first <= 1 || n_swaps == 0)
		return std::string(first, last);

	const auto suffix = first + 1;
	const auto max_digit_in_suffix = *std::max_element(suffix, last);
	if (max_digit_in_suffix <= *first)
		return *first + largest_number(suffix, last, n_swaps);

	std::string max_number;
	for (auto it = suffix; it != last; ++it)
		if (*it == max_digit_in_suffix)
		{
			*it = *first;
			const auto max = largest_number(suffix, last, n_swaps - 1);
			*it = max_digit_in_suffix;
			max_number = std::max(max_number, max);
		}

	return max_digit_in_suffix + max_number;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(n_swaps_);
		read(number_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(largest_number(number_.begin(), number_.end(), n_swaps_));
	}

private:
	std::string number_;
	std::size_t n_swaps_;
};

MAIN

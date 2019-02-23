/*********************************************************************
The archeologists' dilemma
--------------------------
UVa ID: 007 01

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <cmath>

// Returns the minimum power (e) of 2, such that first digits
// of (2^e) are equal to (n), and the total number of digits
// of (2^e) is greater than twice the number of digits of (n)
unsigned int power_of_two_with_first_digits(unsigned int n)
{
	const auto log2_10 = std::log2(10);
	const auto log2_n = std::log2(n);
	const auto log2_np1 = std::log2(n + 1);
	const auto n_digits = static_cast<unsigned int>(std::log10(n)) + 1;
	auto m = n_digits + 1;

	while (true)
	{
		// Note: n1 and n2 before cast are never exact integers
		const auto n1 = static_cast<unsigned int>(m * log2_10 + log2_n);
		const auto n2 = static_cast<unsigned int>(m * log2_10 + log2_np1);
		if (n1 < n2)
			return n2;
		++m;
	}

	assert(false);
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
		write_ln(power_of_two_with_first_digits(n_));
	}

private:
	unsigned int n_;
};

MAIN(CP)

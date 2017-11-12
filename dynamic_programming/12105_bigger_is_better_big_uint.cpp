/*********************************************************************
Bigger is better
----------------
UVa ID: 12105

Goal:	the biggest number that is a multiple of a given number and
		that can be made using a given number of matches.

Note:	this straightforward implementation is slow!

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include "big_uint.hpp"
#include <cstddef>
#include <algorithm>
#include <cassert>

constexpr std::size_t ms_per_digit[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

class Bigger_better : public CP2
{
private:
	virtual bool read_input(std::istream& in) override
	{
		// <number of matches> <divisor>

		in >> n_matches_ >> divisor_;
		if (n_matches_ == 0)
			return false;

		assert(0 < n_matches_ && n_matches_ <= 100);
		assert(0 < divisor_ && divisor_ <= 3000);

		return true;
	}

	virtual void solve(std::ostream& out, std::size_t i_case) override
	{
		/*********************************************************************
		mn(i, j) is the maximum number that can be made using (i) matches and
			that has a remained (j) when it is divided by (divisor).

		The recurrence relation:
			mn(i + ms_per_digit[d], (10 * j + d) % divisor) =
					max {0 <= d <= 9, mn(i, j) is valid} [10 * mn(i, j) + d],
				where (ms_per_digit[d]) is how many matches are needed
				for a (d)-th digit.

		The base case:
			mn(0, 0) = 0.
			mn(i, j) = <invalid> if (i) matches cannot be used to make
								a single digit number with a remainder (j).
		**********************************************************************/

		Matrix<Big_uint> mn(n_matches_ + 1, divisor_, Big_uint::minus_inf());
		mn(0, 0) = 0;

		for (std::size_t i = 0; i < n_matches_; ++i)
			for (unsigned int j = 0; j < divisor_; ++j)
			{
				if (mn(i, j).is_minus_inf())
					continue;

				for (unsigned int d = 0; d < 10; ++d)
				{
					if (i + ms_per_digit[d] > n_matches_)
						continue;

					auto& m = mn(i + ms_per_digit[d], (10 * j + d) % divisor_);
					m = std::max(m, mul_10(mn(i, j)) + d);
				}
			}

		auto max_number = Big_uint::minus_inf();
		for (std::size_t i = 1; i <= n_matches_; ++i)
			max_number = std::max(max_number, mn(i, 0));

		out << "Case " << i_case + 1 << ": ";
		if (max_number.is_finite())
			 out << max_number << '\n';
		else
			out << "-1\n";
	}
		
private:
	std::size_t n_matches_;
	unsigned int divisor_;
};

int main()
{
	Bigger_better p;
	return p.run();
}

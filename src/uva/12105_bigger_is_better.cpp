/*********************************************************************
Bigger is better
----------------
UVa ID: 121 05

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include "util.hpp"
#include <cstddef>
#include <cassert>

constexpr std::size_t ms_per_digit[] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};

class CP : public CP2
{
private:
	static constexpr std::size_t max_size = static_cast<std::size_t>(-1);
	static constexpr signed char invalid_digit = -1;

	struct Number
	{
		std::size_t length = max_size;
		signed char digit = invalid_digit;
	};

private:
	virtual bool read_input() override
	{
		if (!read(n_matches_, divisor_) || n_matches_ == 0)
			return false;

		assert(between(n_matches_, 1, 100));
		assert(between(divisor_, 1, 3000));

		return true;
	}

	virtual void solve(unsigned int i_case) override
	{
		/*********************************************************************
		mn(i, j).length is the length of the maximum number that can be made
			using not more than (i) matches such that its complementary
			number has a remained (j) when it is divided by (divisor),
		mn(i, j).digit is the first (most significant) digit in this number.

			Let the solution be written as (a ... b c d). Then the
			complementary number for a number of length 0 is (a ... b c d),
			of length 1 - (a ... b c), of length 2 - (a ... b), etc.

		The recurrence relation:
			mn(i, j).length = 1 + max {d from 9 to 0, m(., .) in max is valid}
						{m(i - mpd[d], (10 * j + d) % divisor).length},
				where (mpd[d]) = number of matches needed for a (d)-th digit,
			mn(i, j).digit = corresponding (d) is the max.

		The base case:
			mn(i, 0).length = 0,
			mn(i, j > 0).length = <invalid>		for all (i),
		**********************************************************************/

		Matrix<Number> mn(n_matches_ + 1, divisor_, {});
		for (std::size_t i = 0; i <= n_matches_; ++i)
			mn(i, 0).length = 0;

		for (std::size_t i = 0; i <= n_matches_; ++i)
			for (unsigned int j = 0; j < divisor_; ++j)
				for (signed char d = 9; d >= 0; --d)
				{
					if (i < ms_per_digit[d])
						continue;

					auto& m = mn(i, j);
					auto& m_without_d = mn(i - ms_per_digit[d], (10 * j + d) % divisor_);

					if (m_without_d.length != max_size &&
						(m.length < m_without_d.length + 1 || m.length == max_size))
					{
						m.length = m_without_d.length + 1;
						m.digit = d;
					}
				}

		write("Case ", i_case + 1, ": ");

		if (mn(n_matches_, 0).length > 0)
		{
			auto i = n_matches_;
			unsigned int j = 0;
			for (;;)
			{
				const auto& m = mn(i, j);
				assert(m.length != max_size);
				if (m.length == 0)
					break;

				assert(m.digit != invalid_digit);

				i -= ms_per_digit[m.digit];
				j = (10 * j + m.digit) % divisor_;
				assert(i < n_matches_); // Check for "negative" value

				write(static_cast<char>('0' + m.digit));
			}
		}
		else
			write(-1);

		write_ln();
	}

private:
	std::size_t n_matches_;
	unsigned int divisor_;
};

MAIN(CP)

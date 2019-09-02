/*********************************************************************
Divisibility in a binary stream
-------------------------------

For the binary stream check if the number formed so far is divisible
by the given number.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <vector>

template<typename T, class Input_it, class Output_it>
void is_divisible(T divisor, Input_it first, Input_it last, Output_it dest)
{
	T rem = 0;
	while (first != last)
	{
		assert(*first == 0 || *first == 1);
		rem = (2 * rem + *first) % divisor;
		*dest = (rem == 0);
		++first;
		++dest;
	}
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(divisor_);
		ignore_line();

		stream_.clear();
		read_vec_ln(stream_);
	}

	virtual void solve(unsigned int) override
	{
		std::vector<unsigned int> is_div(stream_.size());
		is_divisible(divisor_, stream_.begin(), stream_.end(), is_div.begin());
		for (std::size_t i = 0; i < stream_.size(); ++i)
		{
			write_range(stream_.begin(), stream_.begin() + i + 1, "");
			write_ln(" : ", is_div[i] ? "yes" : "no");
		}
		write_ln();
	}

private:
	unsigned int divisor_;
	std::vector<unsigned int> stream_;
};

MAIN

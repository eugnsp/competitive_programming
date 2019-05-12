/*********************************************************************
Sales
-----
UVa ID: 012 60

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <vector>

using Amount = unsigned int;
using Size = unsigned int;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(amounts_);
	}

	virtual void solve(unsigned int) override
	{
		Size b_sum = 0;
		for (auto i = amounts_.begin() + 1; i != amounts_.end(); ++i)
			for (auto j = amounts_.begin(); j != i; ++j)
				if (*j <= *i)
					++b_sum;

		write_ln(b_sum);
	}

private:
	std::vector<Amount> amounts_;
};

MAIN


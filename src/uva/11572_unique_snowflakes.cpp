/*********************************************************************
Unique snowflakes
-----------------
UVa ID: 115 72

Emily the entrepreneur has a cool business idea: packaging and selling
snowflakes. She has devised a machine that captures snowflakes as they
fall, and serializes them into a stream of snowflakes that flow, one
by one, into a package. Once the package is full, it is closed and
shipped to be sold. The marketing motto for the company is "bags of
uniqueness." To live up to the motto, every snowflake in a package
must be different from the others. Unfortunately, this is easier said
than done, because in reality, many of the snowflakes flowing through
the machine are identical. Emily would like to know the size of the
largest possible package of unique snowflakes that can be created. The
machine can start filling the package at any time, but once it starts,
all snowflakes flowing from the machine must go into the package until
the package is completed and sealed. The package can be completed and
sealed before all of the snowflakes have flowed out of the machine.

Input
-----
The first line of input contains one integer specifying the number
of test cases to follow. Each test case begins with a line containing
an integer n, the number of snowflakes processed by the machine.
The following n lines each contain an integer (in the range 0 to 10^9,
inclusive) uniquely identifying a snowflake. Two snowflakes are
identified by the same integer if and only if they are identical.
The input will contain no more than one million total snowflakes.

Output
------
For each test case output a line containing single integer,
the maximum number of unique snowflakes that can be in a package.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cstddef>
#include <iterator>
#include <unordered_map>
#include <utility>
#include <vector>

template<class It>
std::size_t max_size_unique(It first, const It last)
{
	std::unordered_map<typename std::iterator_traits<It>::value_type, std::size_t> size_index_map;
	std::size_t max_size = 0;
	std::size_t start = 0;
	std::size_t index = 0;

	while (first != last)
	{
		auto& new_start = size_index_map[*first++];
		if (new_start > 0)
		{
			max_size = std::max(max_size, index - start);
			start = std::max(start, new_start);
		}
		new_start = ++index;
	}
	max_size = std::max(max_size, index - start);

	return max_size;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(sizes_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(max_size_unique(sizes_.begin(), sizes_.end()));
	}

private:
	std::vector<unsigned long> sizes_;
};

MAIN

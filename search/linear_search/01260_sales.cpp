/*********************************************************************
Sales
-----
UVa ID: 012 60

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "io.hpp"
#include <cassert>
#include <vector>

using Amount = unsigned int;
using Size = unsigned int;

class CP : public CP1
{
private:
	virtual void read_input(std::istream& in) override
	{
		Size n;
		in >> n;

		assert(2 <= n && n <= 1000);
		read_vector(in, n, amounts_);
	}

	virtual void solve(std::ostream& out, unsigned int) const override
	{
		Size b_sum = 0;
		for (auto i = amounts_.begin() + 1; i != amounts_.end(); ++i)
			for (auto j = amounts_.begin(); j != i; ++j)
				if (*j <= *i)
					++b_sum;

		out << b_sum << '\n';
	}

private:
	std::vector<Amount> amounts_;
};

int main()
{
	CP p;
	return p.run();
}

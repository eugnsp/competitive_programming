/*********************************************************************
Stacks of flapjacks
-------------------
UVa ID: 001 20

Given a stack of pancakes, you are to write a program that indicates
how the stack can be sorted so that the largest pancake is on the
bottom and the smallest pancake is on the top. The size of a pancake
is given by the pancake's diameter. All pancakes in a stack have
different diameters. Sorting a stack is done by a sequence of pancake
"flips". A flip consists of inserting a spatula between two pancakes
in a stack and flipping (reversing) all the pancakes on the spatula
(reversing the sub-stack). A flip is specified by giving the position
of the pancake on the bottom of the sub-stack to be flipped (relative
to the whole stack). The pancake on the bottom of the whole stack has
position 1 and the pancake on the top of a stack of n pancakes has
position n. A stack is specified by giving the diameter of each
pancake in the stack in the order in which the pancakes appear.

Input
-----
The input consists of a sequence of stacks of pancakes. Each stack
will consist of between 1 and 30 pancakes and each pancake will have
an integer diameter between 1 and 100. The input is terminated by
end-of-file. Each stack is given as a single line of input with the
top pancake on a stack appearing first on a line, the bottom pancake
appearing last, and all pancakes separated by a space.

Output
------
For each stack of pancakes, the output should echo the original stack
on one line, followed by some sequence of flips that results in the
stack of pancakes being sorted so that the largest diameter pancake is
on the bottom and the smallest on top. For each stack the sequence of
flips should be terminated bya "0" (indicating no more flips necessary).
Once a stack is sorted, no more flips should be made.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <vector>

using T = int;

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		diams_.clear();
		return read_vec_ln(diams_);
	}

	virtual void solve(unsigned int) override
	{
		write_range(diams_.begin(), diams_.end(), ' ');
		write_ln();

		for (auto last = diams_.end(); last != diams_.begin(); --last)
			if (const auto it = std::max_element(diams_.begin(), last); it + 1 != last)
			{
				if (it != diams_.begin())
				{
					write(diams_.end() - it, ' ');
					std::reverse(diams_.begin(), it + 1);
				}
				write(diams_.end() - last + 1, ' ');
				std::reverse(diams_.begin(), last);
			}

		write_ln(0);
	}

private:
	std::vector<unsigned int> diams_;
};

MAIN

/*********************************************************************
Permutation arrays
------------------
UVa ID: 004 82

In many computer problems, it is necessary to permute data arrays.
That is, the data in an array must be re-arranged in some specified
order. One way to permute arbitrary data arrays is to specify the
permutations with an index array to point out the position of the 
elements in the new array. Let X be an array that is to be permuted
and let X' be the permuted array. Then, we have the relationship
between X and X' is: X'_pi = X_i.

Input
-----
The input begins with a single positive integer on a line by itself
indicating the number of the cases following, each of them as 
described below. This line is followed by a blank line, and there is 
also a blank line between two consecutive inputs. Each input set will
contain two lines of numbers. The first line will be an index array P
containing the integers 1...N, where N is the number of integers in 
the list. The numbers in the first line will have been permuted in 
some fashion. The second line will contain a list numbers in floating 
point format.

Output
------
For each test case, the output must follow the description below. The
outputs of two consecutive cases will be separated by a blank line.
The output for this program will be the list of floating point numbers
from the input set, ordered according to the permutation array from 
the input file. The output numbers must be printed one per line in the
same format in which they each appeared in the input file.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cstddef>
#include <string>
#include <vector>

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		ignore_line();
		read_vec_ln(permutation_);
		read_vec_ln(numbers_);
	}

	virtual void solve(unsigned int i_case) override
	{
		std::vector<std::size_t> inv_permutation(permutation_.size());
		for (std::size_t i = 0; i < permutation_.size(); ++i)
			inv_permutation[permutation_[i] - 1] = i;

		if (i_case > 0)
			write_ln();

		for (auto index : inv_permutation)
			write_ln(numbers_[index]);
	}

private:
	std::vector<std::size_t> permutation_;
	std::vector<std::string> numbers_;
};

MAIN(CP)

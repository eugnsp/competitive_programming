/*********************************************************************
Pizza cutting
-------------
UVa ID: 100 79

Once Ivan was asked to cut a pizza into seven pieces to distribute it
among his friends. Size of the pieces may not be the same. He thought
a bit, and came to the conclusion that he can cut it into seven pieces
by only three straight cuts through the pizza with a pizza knife. One
of his friends was startled at this intelligence. He thought, if Ivan
can do it, why can't my computer? So he tried to do a similar job with
his computer. He wrote a program that took the number of straight cuts
one makes through the pizza, and output a number representing the
maximum number of pizza pieces it will produce. Your job here is to
write a similar program.

Input
-----
The input file will contain a single integer N (0 <= N <= 210'000'000)
in each line representing the number of straight line cuts one makes
through the pizza. A negative number terminates the input.

Output
------
Output the maximum number of pizza pieces the given number of cuts can
produce. Each line should contain only one output integer without any
leading or trailing space.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"

template<typename T>
T central_polygon_number(T n)
{
	return n * (n + 1) / 2 + 1;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		long long n;
		read(n);

		n_ = static_cast<unsigned long long>(n);
		return n >= 0;
	}

	virtual void solve(unsigned int) override
	{
		write_ln(central_polygon_number(n_));
	}

private:
	unsigned long long n_;
};



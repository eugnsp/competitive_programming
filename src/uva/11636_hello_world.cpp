/*********************************************************************
Hello, world!
-------------
UVa ID: 116 36

When you first made the computer to print the sentence "Hello, World!",
you felt so happy, not knowing how complex and interesting the world
of programming and algorithm will turn out to be. Then you did not
know anything about loops, so to print 7 lines of "Hello, World!", you
just had to copy and paste some lines. If you were intelligent enough,
you could make a code that prints "Hello, World!" 7 times, using just
3 paste commands. Note that we are not interested about the number of
copy commands required. Given the number of "Hello, World!" lines you
need to print, you will have to find out the minimum number of pastes
required to make that program.

Input
-----
The input file can contain up to 2000 lines of inputs. Each line
contains an integer N (0 < N < 10001) that denotes the number of
"Hello, World!" lines are required to be printed. Input is terminated
by a line containing a negative integer.

Output
------
For each line of input except the last one, produce one line of output
of the form "Case X: Y" where X is the serial of output and Y denotes
the minimum number of paste commands required to make a program that
prints N lines of "Hello, World!".

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>

template<typename N>
N ceil_log2(N n)
{
	assert(n > 0);

	N log2 = 0;
	for (--n; n > 0; n /= 2)
		++log2;

	return log2;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(n_) && n_ > 0;
	}

	virtual void solve(unsigned int i_case) override
	{
		write_ln("Case ", i_case, ": ", ceil_log2(n_));
	}

private:
	int n_;
};

MAIN


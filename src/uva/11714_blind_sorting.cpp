/*********************************************************************
Blind sorting
-------------
UVa ID: 117 14

I am a polar bear. But I am not just an ordinary polar bear. Yes I am
extra ordinary! I love to play with numbers.  One day my very good
friend Mr. Panda came to me, and challenged me to solve apuzzle. He
blindfolded me, and said that I have n distinct numbers. What I can
ask is whether a-th number is larger than b-th number and he will
answer me properly. What I have to do is to find out the largest and
second largest number. I thought for a while and said "Come on, I will
do it in minimum number of comparison."

Input
-----
There will be a non-negative integer, n in each of the line of input
where n is as described above. n will be less than any 10 digit prime
number and not less than the smallest prime.

Output
------
For each n, output number of questions that I have to ask Mr. Panda in
the worst case.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(n_);
	}

	virtual void solve(unsigned int) override
	{
		unsigned int ceil_log_n = 0;
		for (unsigned int i = 1; i < n_; i *= 2)
			++ceil_log_n;

		write_ln(n_ + ceil_log_n - 2);
	}

private:
	unsigned int n_;
};

MAIN(CP)

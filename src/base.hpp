// Base classes and general routines
// ---------------------------------
//
// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include "io.hpp"
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <type_traits>

class CP0
{
public:
	CP0()
	{
		std::ios_base::sync_with_stdio(false);

	#ifdef ONLINE_JUDGE
		istream = &std::cin;
	#else
		file_.open("input.txt");
		assert(file_);

		istream = &file_;
	#endif
	}

private:
#ifndef ONLINE_JUDGE
	std::ifstream file_;
#endif
};

// Number of test cases is given at the first line
class CP1 : public CP0
{
public:
	int run()
	{
		init();

		unsigned int n_test_cases;
		(*istream) >> n_test_cases;
		ignore_line();

		for (unsigned int i = 0; i < n_test_cases; ++i)
		{
			read_input();
			assert(!istream->bad());
			solve(i);
		}

		end();
		return 0;
	}

protected:
	virtual void init()
	{}
	virtual void read_input() = 0;
	virtual void solve(unsigned int) = 0;
	virtual void end()
	{}
};

// Number of test cases is not given explicitly, termination condition is defined
class CP2 : public CP0
{
public:
	int run()
	{
		init();

		unsigned int i = 0;
		while (read_input())
		{
			assert(!istream->bad());
			solve(i++);
		}

		end();
		return 0;
	}

protected:
	virtual void init()
	{}
	virtual bool read_input() = 0;
	virtual void solve(unsigned int) = 0;
	virtual void end()
	{}
};

// Single test case
class CP3 : public CP0
{
public:
	int run()
	{
		init();

		read_input();
		assert(!istream->bad());
		solve();

		end();
		return 0;
	}

protected:
	virtual void init()
	{}
	virtual void read_input() = 0;
	virtual void solve() = 0;
	virtual void end()
	{}
};

#define MAIN(x)                                                                                    \
	int main()                                                                                     \
	{                                                                                              \
		x p;                                                                                       \
		return p.run();                                                                            \
	}

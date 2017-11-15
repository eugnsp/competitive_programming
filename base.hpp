// Base classes and general routines
// ---------------------------------
//
// This file is covered by the LICENSE file in the root of this project.

#pragma once

#ifdef ONLINE_JUDGE
#define NDEBUG
#endif

#include <cstddef>
#include <limits>
#include <iostream>
#include <cassert>

#ifndef ONLINE_JUDGE
#include <fstream>
#endif

class CP1
{
public:
	int run()
	{
		std::ios_base::sync_with_stdio(false);

		init();

	#ifdef ONLINE_JUDGE
		auto& in = std::cin;
	#else
		std::ifstream f("input.txt");
		auto& in = f;
	#endif

		std::size_t n_test_cases;
		in >> n_test_cases;
		in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		for (std::size_t i = 0; i < n_test_cases; ++i)
		{
			read_input(in);
			assert(in);
			solve(std::cout, i);
		}

		end(std::cout);

		return 0;
	}

protected:
	virtual void init()
	{ }

	virtual void end(std::ostream&)
	{ }
	
	virtual void read_input(std::istream&) = 0;
	virtual void solve(std::ostream&, std::size_t) = 0;
};

class CP2
{
public:
	int run()
	{
		std::ios_base::sync_with_stdio(false);
		
		init();

	#ifdef ONLINE_JUDGE
		auto& in = std::cin;
	#else
		std::ifstream f("input.txt");
		auto& in = f;
	#endif
		
		std::size_t i = 0;
		while (read_input(in))
		{
			assert(in);
			solve(std::cout, i++);
		}

		end(std::cout);

		return 0;
	}

protected:
	virtual void init()
	{ }

	virtual void end(std::ostream&)
	{ }
	
	virtual bool read_input(std::istream&) = 0;
	virtual void solve(std::ostream&, std::size_t) = 0;
};

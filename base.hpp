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

class CP1
{
public:
	int run()
	{
		std::ios_base::sync_with_stdio(false);
		init();

		std::size_t n_test_cases;
		std::cin >> n_test_cases;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		for (std::size_t i = 0; i < n_test_cases; ++i)
		{
			read_input(std::cin);
			assert(std::cin);
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

		std::size_t i = 0;
		while (read_input(std::cin))
		{
			assert(std::cin);
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

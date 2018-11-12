// Base classes and general routines
// ---------------------------------
//
// This file is covered by the LICENSE file in the root of this project.

#pragma once

#ifdef ONLINE_JUDGE
#define NDEBUG
#endif

#include <cassert>
#include <iostream>
#include <limits>
#include <utility>

inline void ignore_line(std::istream& in)
{
	in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

class CP1
{
public:
	int run()
	{
		std::ios_base::sync_with_stdio(false);
		init();

		unsigned int n_test_cases;
		std::cin >> n_test_cases;
		ignore_line(std::cin);

		for (unsigned int i = 0; i < n_test_cases; ++i)
		{
			read_input(std::cin);
			assert(!std::cin.bad());
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
	virtual void solve(std::ostream&, unsigned int) const = 0;
};

class CP2
{
public:
	int run()
	{
		std::ios_base::sync_with_stdio(false);
		init();

		unsigned int i = 0;
		while (read_input(std::cin))
		{
			assert(!std::cin.bad());
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
	virtual void solve(std::ostream&, unsigned int) const = 0;
};

class CP3
{
public:
	int run()
	{
		std::ios_base::sync_with_stdio(false);
		init();

		read_input(std::cin);
		assert(!std::cin.bad());
		solve(std::cout);

		end(std::cout);
		return 0;
	}

protected:
	virtual void init()
	{ }

	virtual void end(std::ostream&)
	{ }
	
	virtual void read_input(std::istream&) = 0;
	virtual void solve(std::ostream&) const = 0;
};

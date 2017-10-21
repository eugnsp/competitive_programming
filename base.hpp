#pragma once
#include <cstddef>
#include <limits>
#include <iostream>

class Program1
{
public:
	int run()
	{
		std::size_t n_test_cases;
		std::cin >> n_test_cases;
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

		for (std::size_t i = 0; i < n_test_cases; ++i)
		{
			read_input();
			solve(i);
		}

		return 0;
	}

protected:
	virtual void read_input() = 0;
	virtual void solve(std::size_t) = 0;
};

class Program2
{
public:
	int run()
	{
		for (std::size_t i = 0; true; ++i)
		{
			if (!read_input())
				break;
			solve(i);
		}

		return 0;
	}

protected:
	virtual bool read_input() = 0;
	virtual void solve(std::size_t) = 0;
};
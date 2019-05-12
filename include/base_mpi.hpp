// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include "io.hpp"
#include "mpi.hpp"
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
		MPI_Init(nullptr, nullptr);

		int mpi_size, mpi_rank;
		MPI_Comm_size(MPI_COMM_WORLD, &mpi_size);
		MPI_Comm_rank(MPI_COMM_WORLD, &mpi_rank);

		mpi_size_ = static_cast<unsigned int>(mpi_size);
		mpi_rank_ = static_cast<unsigned int>(mpi_rank);

		std::ios_base::sync_with_stdio(false);

#ifdef OFFLINE_JUDGE
		file_.open("input.txt");
		assert(file_);
		istream = &file_;

		std::cout << std::unitbuf;
#else
		istream = &std::cin;
#endif
	}

	~CP0()
	{
		MPI_Finalize();
	}

protected:
	unsigned int mpi_size_;
	unsigned int mpi_rank_;

private:
#ifdef OFFLINE_JUDGE
	std::ifstream file_;
#endif
};

// Number of test cases is given at the first line
class CP1 : public CP0
{
public:
	int run()
	{
		unsigned int n_test_cases;
		if (mpi_rank_ == 0)
		{
			(*istream) >> n_test_cases;
			ignore_line();
		}

		mpi_bcast(n_test_cases);
		for (unsigned int i = 1; i <= n_test_cases; ++i)
		{
			if (mpi_rank_ == 0)
			{
				read_input();
				assert(!istream->bad());
				solve_master(i);
				std::cout.flush();
			}
			else
				solve_slave(i);
		}

		return 0;
	}

protected:
	virtual void read_input() = 0;
	virtual void solve_master(unsigned int) = 0;
	virtual void solve_slave(unsigned int) = 0;
};

// Single test case
class CP3 : public CP0
{
public:
	int run()
	{
		if (mpi_rank_ == 0)
		{
			read_input();
			assert(!istream->bad());
			solve_master();
			std::cout.flush();
		}
		else
			solve_slave();

		return 0;
	}

protected:
	virtual void read_input() = 0;
	virtual void solve_master() = 0;
	virtual void solve_slave() = 0;
};

#define MAIN                                                                                                           \
	int main()                                                                                                         \
	{                                                                                                                  \
		CP app;                                                                                                        \
		return app.run();                                                                                              \
	}

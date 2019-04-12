/*********************************************************************
Vector addition
---------------
IHPC ID: P1

Given two vectors of dimension N, output the vector sum.

Input
-----
The first line contains an integer T (1 <= T <= 100), the number of
test cases. The second line contains an integer, n (1 <= n <= 1'000'000),
the dimension of the vectors. It is followed by two lines containing
n space-separated integers each, representing the vector A and B
to be added.

Output
------
On a single line, output n space separated integers representing the
vector A + B. Note: Print a new line between the result of test cases.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base_mpi.hpp"
#include "mpi.h"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <thread>
#include <vector>

std::size_t mpi_block_size(std::size_t size, int mpi_rank, int mpi_size)
{
	const auto n_max_per_slave = size / mpi_size;
	const auto rem = static_cast<int>(size % mpi_size);
	const auto r_rank = mpi_size - 1 - mpi_rank;

	return n_max_per_slave + (r_rank < rem);
}

std::size_t mpi_block_offset(std::size_t size, int mpi_rank, int mpi_size)
{
	const auto n_max_per_slave = size / mpi_size;
	const auto rem = static_cast<int>(size % mpi_size);
	const auto r_rank = mpi_size - 1 - mpi_rank;

	return n_max_per_slave * r_rank + std::min(r_rank, rem);
}

template<class It>
void add(It first1, It last1, It first2)
{
	while (first1 != last1)
		*first1++ += *first2++;
}

template<class It>
void parallel_add(It first1, It last1, It first2)
{
	const auto size = static_cast<std::size_t>(last1 - first1);
	const auto n_threads = std::thread::hardware_concurrency();
	const auto n_max_per_thread = (size + n_threads - 1) / n_threads;

	const auto add = [](It first1, It first2, std::size_t count)
	{
		while (count-- > 0)
			*first1++ += *first2++;
	};

	std::vector<std::thread> workers;
	while (first1 != last1)
	{
		const auto n = std::min(n_max_per_thread, static_cast<std::size_t>(last1 - first1));
		workers.push_back(std::thread{add, first1, first2, n});

		first1 += n;
		first2 += n;
	}

	for (auto& w : workers)
		w.join();
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t size;
		read(size);

		a_.clear();
		b_.clear();
		read_vec(size, a_);
		read_vec(size, b_);
	}

	virtual void solve_master(unsigned int) override
	{
		const std::size_t size = a_.size();
		mpi_bcast(const_cast<std::size_t*>(&size), 1);

		for (int r = 1; r < mpi_size_; ++r)
			if (const auto block_size = mpi_block_size(size, r, mpi_size_); block_size > 0)
			{
				const auto block_offset = mpi_block_offset(size, r, mpi_size_);
				assert(block_offset < size);

				mpi_send(a_.data() + block_offset, block_size, r);
				mpi_send(b_.data() + block_offset, block_size, r);
			}

		const auto block_offset = mpi_block_offset(size, 0, mpi_size_);
		const auto block_end = block_offset + mpi_block_size(size, 0, mpi_size_);

		parallel_add(a_.begin() + block_offset, a_.begin() + block_end, b_.begin() + block_offset);

		for (int r = 1; r < mpi_size_; ++r)
			if (const auto block_size = mpi_block_size(size, r, mpi_size_); block_size > 0)
			{
				const auto block_offset = mpi_block_offset(size, r, mpi_size_);
				assert(block_offset < size);
				mpi_recv(a_.data() + block_offset, block_size, r);
			}

		write_range(a_.begin(), a_.end(), ' ');
		write_ln();
	}

	virtual void solve_slave(unsigned int) override
	{
		std::size_t size;
		mpi_bcast(&size, 1);

		const auto block_size = mpi_block_size(size, mpi_rank_, mpi_size_);
		if (block_size == 0)
			return;

		a_.resize(block_size);
		b_.resize(block_size);

		mpi_recv(a_.data(), block_size, 0);
		mpi_recv(b_.data(), block_size, 0);

		parallel_add(a_.begin(), a_.end(), b_.begin());
		mpi_send(a_.data(), block_size, 0);
	}

private:
	std::vector<int> a_, b_;
};

/*********************************************************************
Vector addition
---------------
ID: P1

Given two vectors of dimension n, output the vector sum.

Input
-----
The first line contains an integer T (1 <= T <= 100), the number of
test cases. The second line contains an integer, n (1 <= n <= 1'000'000),
the dimension of the vectors. It is followed by two lines containing
n space-separated integers each, representing the vector A and B
to be added.

Output
------
On a single line, output n space separated integers representing
the vector A + B.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

// Note: this is just a tutorial problem, computing a vector sum using
// MPI in this way is an insane thing to do.

#include "base_mpi.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <thread>
#include <utility>
#include <vector>

template<typename T>
std::pair<T, T> block_size_and_offset(T size, unsigned int mpi_rank, unsigned int mpi_size)
{
	const auto n_max_per_slave = size / mpi_size;
	const T rem = size % mpi_size;
	const T r_rank = mpi_size - 1 - mpi_rank;

	return {n_max_per_slave + (r_rank < rem), n_max_per_slave * r_rank + std::min(r_rank, rem)};
}

template<class It>
void parallel_add(It first1, It first2, std::size_t count)
{
	const auto n_threads = std::thread::hardware_concurrency();
	const auto n_max_per_thread = (count + n_threads - 1) / n_threads;

	const auto adder = [](It first1, It first2, std::size_t count)
	{
		while (count-- > 0)
			*first1++ += *first2++;
	};

	std::vector<std::thread> workers;
	while (count > 0)
	{
		const auto n = std::min(n_max_per_thread, count);
		workers.emplace_back(adder, first1, first2, n);

		first1 += n;
		first2 += n;
		count -= n;
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
		mpi_bcast(size);

		std::vector<int> b_sizes;
		std::vector<int> b_offsets;
		for (auto r = 0u; r < mpi_size_; ++r)
		{
			const auto [b_size, b_offset] = block_size_and_offset(size, r, mpi_size_);
			b_sizes.push_back(static_cast<int>(b_size));
			b_offsets.push_back(static_cast<int>(b_offset));
		}

		mpi_scatterv_send(a_.data(), b_sizes, b_offsets);
		mpi_scatterv_send(b_.data(), b_sizes, b_offsets);

		parallel_add(
			a_.begin() + b_offsets.front(), b_.begin() + b_offsets.front(), b_sizes.front());

		mpi_gatherv_recv(a_.data(), b_sizes, b_offsets);
		write_range(a_.begin(), a_.end(), ' ');
		write_ln();
	}

	virtual void solve_slave(unsigned int) override
	{
		std::size_t size;
		mpi_bcast(size);

		const auto b_size = block_size_and_offset(size, mpi_rank_, mpi_size_).first;
		a_.resize(b_size);
		b_.resize(b_size);

		mpi_scatterv_recv(a_.data(), b_size);
		mpi_scatterv_recv(b_.data(), b_size);

		parallel_add(a_.begin(), b_.begin(), b_size);
		mpi_gatherv_send(a_.data(), b_size);
	}

private:
	std::vector<int> a_, b_;
};

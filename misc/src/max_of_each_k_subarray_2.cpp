/*********************************************************************
Maximum of each subarray
------------------------

Find the maximum for each contiguous subarray of the given size in
the given array.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <deque>
#include <vector>
#include <cstddef>

template<class It>
void pop_back_smaller_and_push_back(std::deque<It>& deque, const It& it)
{
	while (!deque.empty() && *deque.back() <= *it)
		deque.pop_back();
	deque.push_back(it);
}

template<class It>
void pop_front_before(std::deque<It>& deque, const It& it)
{
	while (!deque.empty() && deque.front() <= it)
		deque.pop_front();
}

// Overwrites the first n = (last - first - k + 1) elements of
// the range [first, last) with the maximum values in each
// subrange [first + i, first + i + k) for i = 0, ..., n - 1
template<class It, typename Size>
void max_subarrays_n(It first, const It last, Size k)
{
	assert(k >= 1);
	assert(k <= last - first);

	std::deque<It> deque;

	auto right = first;
	while (k-- > 0)
	{
		pop_back_smaller_and_push_back(deque, right++);
	}

	auto left = first;
	while (true)
	{
		*left = *deque.front();
		if (right == last)
			break;
		pop_front_before(deque, left++);
		pop_back_smaller_and_push_back(deque, right++);
	}
}

std::vector<int>* seq;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t size;
		read(size, k_);
		seq_.clear();
		read_vec(size, seq_);
	}

	virtual void solve(unsigned int) override
	{
		seq = &seq_;
		max_subarrays_n(seq_.begin(), seq_.end(), k_);
		write_range(seq_.begin(), seq_.end() - (k_ - 1), ' ');
		write_ln();
	}

private:
	std::vector<int> seq_;
	std::size_t k_;
};

MAIN

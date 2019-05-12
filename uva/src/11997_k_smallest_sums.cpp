/*********************************************************************
K smallest sums
---------------
UVa ID: 119 97

You're given K arrays, each array has K integers. There are K ways
to pick exactly one element in each array and calculate the sum of
the integers. Your task is to find the K smallest sums among them.

Input
-----
There will be several test cases. The first line of each case contains
an integer K (2 <= K <= 750). Each of the following K lines contains
K positive integers in each array. Each of these integers does not
exceed 1'000'000. The input is terminated by end-of-file (EOF).

Output
------
For each test case, print the K smallest sums, in ascending order.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <queue>
#include <utility>
#include <vector>

using T = unsigned int;

// Computes (n) smallest sums of the form (vec1[...] + vec2[...]),
// where (n) is the size of (vec1); stores the result in (vec1);
// (vec2) should be sorted in non-descreasing order
void merge_sum(std::vector<T>& vec1, const std::vector<T>& vec2)
{
	struct Node
	{
		T sum;
		std::vector<T>::const_iterator second_term;

		bool operator<(const Node& other) const
		{
			return other.sum < sum;
		}
	};

	assert(std::is_sorted(vec2.begin(), vec2.end()));

	std::vector<Node> min_heap_container;
	min_heap_container.reserve(vec1.size());
	for (auto v : vec1)
		min_heap_container.push_back({v + vec2[0], vec2.begin()});

	std::priority_queue<Node> min_heap({}, std::move(min_heap_container));

	std::size_t k = 0;
	while (true)
	{
		assert(!min_heap.empty());
		auto sum = min_heap.top();
		min_heap.pop();

		vec1[k++] = sum.sum;
		if (k == vec1.size())
			break;

		if (++sum.second_term != vec2.end())
		{
			sum.sum += *sum.second_term - *(sum.second_term - 1);
			min_heap.push(sum);
		}
	}
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		if (!read(n_))
			return false;

		data_.assign(n_, {});
		for (std::size_t k = 0; k < n_; ++k)
			read_vec(n_, data_[k]);

		return true;
	}

	virtual void solve(unsigned int) override
	{
		auto& dest = data_[0];
		for (std::size_t row = 1; row < n_; ++row)
		{
			std::sort(data_[row].begin(), data_[row].end());
			merge_sum(dest, data_[row]);
		}

		write_vec(dest, ' ');
		write_ln();
	}

private:
	std::size_t n_;
	std::vector<std::vector<T>> data_;
};

MAIN


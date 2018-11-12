/*********************************************************************
Ultra-QuickSort
---------------
UVa ID: 108 10

In this problem, you have to analyze a particular sorting algorithm.
The algorithm processes a sequence of N distinct integers by swapping
two adjacent equence elements until the sequence is sorted in
ascending order. For the input sequence {9 1 0 5 4}, Ultra-QuickSort
produces the output {0 1 4 5 9}. Your task is to determine how many
swap operations Ultra-QuickSort needs to perform in order to sort
a given input sequence.

Input
-----
The input contains several test cases. Every test case begins with a
line that contains a single integer N < 500'000 - the length of the
input sequence. Each of the the following N lines contains a single
integer 0 <= a[i] < 1'000'000'000, the i-th input sequence element.
Input is terminated by a sequence of length N = 0. This sequence must
not be processed.

Output
------
For every input sequence, your program prints a single line containing
an integer number OP, the minimum number of swap operations necessary
to sort the given input sequence.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <vector>

using T = unsigned int;
using Count = unsigned long long;

template<class It>
Count insertion_sort_and_count_inversions(It first, It last)
{
	assert(first <= last);
	if (last - first <= 1)
		return 0;

	Count inv_count = 0;

	auto end = std::next(first);
	while (end != last)
	{
		auto end_element = *end;

		auto pos = end;
		while (pos > first && *std::prev(pos) > end_element)
		{
			*pos = *std::prev(pos);
			--pos;
			++inv_count;
		}

		*pos = end_element;
		++end;
	}

	return inv_count;
}

template<class It>
Count merge_sort_and_count_inversions(It first, It mid, It last, It dest)
{
	Count inv_count = 0;

	auto it1 = first;
	auto it2 = mid;
	while (it1 != mid && it2 != last)
	{
		if (*it1 <= *it2)
		{
			*dest++ = *it1++;
			inv_count += (it2 - mid);
		}
		else
			*dest++ = *it2++;
	}

	std::copy(it1, mid, dest);
	std::copy(it2, last, dest);
	inv_count += (mid - it1) * (last - mid);

	return inv_count;
}

template<class It>
Count count_inversions_impl(It first, It last, It buff, bool in_place)
{
	assert(first <= last);
	if (last - first <= 100)
	{
		const auto inv_count = insertion_sort_and_count_inversions(first, last);
		if (!in_place)
			std::copy(first, last, buff);
		return inv_count;
	}

	const auto mid = first + (last - first) / 2;
	const auto buff_mid = buff + (mid - first);
	const auto buff_last = buff + (last - first);

	auto inv_count = count_inversions_impl(first, mid, buff, !in_place);
	inv_count += count_inversions_impl(mid, last, buff_mid, !in_place);

	inv_count += in_place
		? merge_sort_and_count_inversions(buff, buff_mid, buff_last, first)
		: merge_sort_and_count_inversions(first, mid, last, buff);

	return inv_count;
}

template<class It>
Count count_inversions(It first, It last)
{
	using T = typename std::iterator_traits<It>::value_type;
	std::vector<T> buff(last - first);
	return count_inversions_impl(first, last, buff.begin(), true);
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_size_vec(values_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(count_inversions(values_.begin(), values_.end()));
	}

private:
	std::vector<T> values_;
};

MAIN(CP)

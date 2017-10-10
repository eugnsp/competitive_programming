// Kadane's algorithm common routines
//
// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <iterator>
#include <algorithm>
#include <limits>
#include <cassert>

// Returns the sum of contiguous subarray within the array ([first, last))
// which has the largest sum
template<class T_Forward_iterator>
typename std::iterator_traits<T_Forward_iterator>::value_type
	kadane_max_sum(T_Forward_iterator first, T_Forward_iterator last)
{
	assert(first != last);

	using Value = typename std::iterator_traits<T_Forward_iterator>::value_type;

	auto sum = std::numeric_limits<Value>::min();
	auto max_sum = sum;	

	for (; first != last; ++first)
	{
		if (sum >= 0)
			sum += *first;
		else
			sum = *first;

		max_sum = std::max(max_sum, sum);
	}

	return max_sum;
}

// Finds the contiguous subarray within the array ([first, last))
// which has the largest sum, and returns the sum and the subarray range
// (for two or more such subarrays the longest one is returned,
// for two or more longest subarrays the first one is returned)
template<class T_Forward_iterator>
std::pair<typename std::iterator_traits<T_Forward_iterator>::value_type,
	std::pair<T_Forward_iterator, T_Forward_iterator>>
	kadane_max_sum_and_range(T_Forward_iterator first, T_Forward_iterator last)
{
	using Value = typename std::iterator_traits<T_Forward_iterator>::value_type;

	assert(first != last);

	auto sum = std::numeric_limits<Value>::min();
	auto max_sum = sum;

	auto start = first;
	auto max_start = start;

	auto end = first;
	auto max_end = end;

	std::size_t length = 0;
	std::size_t max_length = length;

	for (; first != last; ++first)
	{
		if (sum >= 0)
			sum += *first;
		else
		{
			sum = *first;
			start = end = first;
			length = 0;
		}

		++end;
		++length;

		if (sum > max_sum || (sum == max_sum && length > max_length))
		{
			max_sum = sum;

			max_start = start;
			max_end = end;
			max_length = length;
		}
	}

	return {max_sum,{max_start, max_end}};
}

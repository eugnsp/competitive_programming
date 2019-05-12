/*********************************************************************
Copying books
-------------
UVa ID: 007 14

Imagine you have m books (numbered 1, 2, ..., m) that may have
different number of pages (p1, p2, ..., pm) and you want to make one
copy of each of them. Your task is to divide these books among k
scribes, k <= m. Each book can be assigned to a single scriber only,
and every scriber must get a continuous sequence of books. That means,
there exists an increasing succession of numbers
	0 = b0 < b1 < b2 < ... < bk = m
such that i-th scriber gets a sequence of books with numbers between
b(i-1) + 1 and bi. The time needed to make a copy ofall the books is
determined by the scriber who was assigned the most work. Therefore,
our goal is to minimize the maximum number of pages assigned to a
single scriber. Your task is to find the optimal assignment.

Input
-----
The input consists of N cases. The first line of the input contains
only positive integer N. Then follow the cases. Each case consists of
exactly two lines. At the first line, there are two integers m and k,
1 <= k <= m <= 500. At the second line, there are integers
p1, p2, ..., pm separated by spaces. All these values are positive
and less than 10'000'000.

Output
------
For each case, print exactly one line. The line must contain the input
succession p1, p2, ..., pm divided into exactly k parts such that the
maximum sum of a single part should be as small as possible. Use the
slash character "/"" to separate the parts. There must be exactly one
space character between any two successive numbers and between the
number and the slash. If there is more than one solution, print the
one that minimizes the work assigned to the first scriber, then to the
second scriber etc. But each scriber must be assigned at least one book.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <vector>

template<class It, typename T>
bool is_partition_possible(const It first, const It last, const std::size_t n_groups, const T range_sum)
{
	std::size_t g = 0;
	auto curr_sum = static_cast<T>(0);

	for (auto it = first; it != last; ++it)
	{
		curr_sum += *it;
		if (curr_sum > range_sum)
		{
			if (++g >= n_groups)
				return false;
			curr_sum = *it;
		}
	}

	return true;
}

template<class It, typename T = typename std::iterator_traits<It>::value_type>
T min_range_sum(const It first, const It last, const std::size_t n_groups)
{
	assert(n_groups != 0);
	assert(static_cast<std::size_t>(last - first) >= n_groups);

	// [left, right] contains the minimum possible value in the set
	// of all range sums; at the beginning: left = max vi, right = sum vi;
	// at the end: left = right

	auto left = static_cast<T>(0);
	auto right = static_cast<T>(0);

	for (auto it = first; it != last; ++it)
	{
		left = std::max(left, *it);
		right += *it;
	}

	while (left < right)
	{
		const auto sum = (left + right) / 2;
		if (is_partition_possible(first, last, n_groups, sum))
			right = sum;
		else
			left = sum + 1;
	}

	return left;
}

template<class It>
std::vector<It> minimizing_partition(const It first, const It last, const std::size_t n_groups)
{
	assert(n_groups != 0);
	assert(static_cast<std::size_t>(last - first) >= n_groups);

	const auto sum = min_range_sum(first, last, n_groups);

	std::vector<It> partition(n_groups);
	auto g = n_groups - 1;

	const auto rlast = std::reverse_iterator<It>{first};
	for (auto it = std::reverse_iterator<It>{last}; it != rlast;)
	{
		auto curr_sum = static_cast<decltype(sum)>(0);
		while (it != rlast && curr_sum + *it <= sum && g < static_cast<std::size_t>(rlast - it))
			curr_sum += *it++;

		partition[g--] = it.base();
	}

	return partition;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t n_books;
		read(n_books, n_scribers_);

		book_sizes_.clear();
		read_vec(n_books, book_sizes_);
	}

	virtual void solve(unsigned int) override
	{
		auto part = minimizing_partition(book_sizes_.begin(), book_sizes_.end(), n_scribers_);

		for (std::size_t p = 0; p < part.size() - 1; ++p)
		{
			write_range(part[p], part[p + 1], ' ');
			std::cout << " / ";
		}
		write_range(part.back(), book_sizes_.end(), ' ');
		write_ln();
	}

private:
	std::vector<unsigned int> book_sizes_;
	std::size_t n_scribers_;
};

MAIN


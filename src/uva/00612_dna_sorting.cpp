/*********************************************************************
DNA sorting
-----------
UVa ID: 006 12

One measure of "unsortedness" in a sequence is the number of pairs of
entries that are out of order with respect to each other. For instance,
in the letter sequence "DAABEC", this measure is 5, since D is greater
than four letters to its right and E is greater than one letter to its
right. This measure is called the number of inversions in the sequence.
The sequence "AACEDGG" has only one inversion (E and D) - it is nearly
sorted - while the sequence "ZWQM" has 6 inversions (it is as unsorted
as can be - exactly the reverse of sorted). You are responsible for
cataloguing a sequence of DNA strings (sequences containing only the
four letters A, C, G, and T). However, you want to catalog them, not
in alphabetical order, but rather inorder of "sortedness", from "most
sorted" to "least sorted". All the strings are of the same length.

Input
-----
The first line of the input is an integer M, then a blank line
followed by M datasets. There is a blank line between datasets. The
first line of each dataset contains two integers: a positive integer
n (0 < n <= 50) giving the length of the strings; and a positive
integer m (0 < m <= 100) giving the number of strings. These are
followed by m lines, each containing a string of length n.

Output
------
For each dataset, output the list of input strings, arranged from "most
sorted" to "least sorted". If two or more strings are equally sorted,
list them in the same order they are in the input file. Print a blank
line between consecutive test cases.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

template<class It>
std::size_t merge_and_count_inversions(const It first, const It mid, const It last)
{
	std::vector<typename std::iterator_traits<It>::value_type> buff;
	buff.reserve(last - first);

	std::size_t cnt = 0;

	auto it1 = first;
	auto it2 = mid;
	while (it1 != mid && it2 != last)
		if (*it2 < *it1)
		{
			buff.push_back(std::move(*it2++));
			cnt += mid - it1;
		}
		else
			buff.push_back(std::move(*it1++));

	std::move(it1, mid, std::back_inserter(buff));
	std::move(it2, last, std::back_inserter(buff));

	std::move(buff.begin(), buff.end(), first);
	return cnt;
}

template<class It>
std::size_t count_inversions(const It first, const It last)
{
	if (last - first <= 2)
	{
		if (last - first == 2 && *(first + 1) < *first)
		{
			std::iter_swap(first, first + 1);
			return 1;
		}
		return 0;
	}

	const auto mid = first + (last - first) / 2;

	std::size_t cnt = 0;
	cnt += count_inversions(first, mid);
	cnt += count_inversions(mid, last);
	cnt += merge_and_count_inversions(first, mid, last);

	return cnt;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t str_len, size;
		read(str_len);
		read(size);

		strings_.clear();
		strings_.reserve(size);
		while (size-- > 0)
		{
			std::string str;
			str.reserve(str_len);
			read(str);
			strings_.push_back(std::move(str));
		}
	}

	virtual void solve(unsigned int i_case) override
	{
		if (i_case > 0)
			write_ln();

		auto strings = strings_;
		std::vector<std::pair<std::size_t, std::size_t>> inv_counter_;
		inv_counter_.reserve(strings.size());

		for (std::size_t i = 0; i < strings.size(); ++i)
			inv_counter_.emplace_back(count_inversions(strings[i].begin(), strings[i].end()), i);

		std::sort(inv_counter_.begin(), inv_counter_.end());
		for (auto& i : inv_counter_)
			write_ln(strings_[i.second]);
	}

private:
	std::vector<std::string> strings_;
};



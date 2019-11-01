/*********************************************************************
Distinct substring
------------------
UVa ID: 124 94

Given a string S, Dexter wants to find the number of different
substrings in S. He considers two substrings same if they have 
a cyclic permutation which is same.

Input
-----
First line contains an integer T (T <= 50) denoting the number of
test cases. Each of the next T lines contains a string S which is
composed of only lowercase latin letters. You can assume that the
length of S is between 1 and 200 inclusive.

Output
------
For each test case, output the number of different substrings in
a line.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <string>
#include <unordered_set>

template<class It>
class Circular_view
{
public:
	Circular_view(It first, It start, It last) : first_(first), start_(start), last_(last)
	{
		assert(first <= start);
		assert(start < last);
	}

	std::size_t length() const
	{
		return static_cast<std::size_t>(last_ - first_);
	}

	bool operator==(const Circular_view& other) const
	{
		if (length() != other.length())
			return false;

		auto it = other.start_;
		const auto is_equal = [&](char ch) {
			if (*it != ch)
				return false;
			if (++it == other.last_)
				it = other.first_;
			return true;
		};

		return for_each(is_equal);
	}

	template<class Fn>
	bool for_each(Fn&& fn) const
	{
		auto it = start_;
		do
		{
			if (!fn(*it))
				return false;
			if (++it == last_)
				it = first_;
		} while (it != start_);

		return true;
	}

private:
	const It first_;
	const It start_;
	const It last_;
};

template<class It>
struct std::hash<Circular_view<It>>
{
	std::size_t operator()(const Circular_view<It>& view) const
	{
		std::size_t hash = 0x811c9dc5ul;
		view.for_each([&hash](char ch) {
			hash = (hash * 0x01000193ul) ^ ch;
			return true;
		});
		return hash;
	}
};

template<class It>
It cyclic_advance(It it, It first, It last, std::size_t step)
{
	const auto max_step = static_cast<size_t>(last - it);
	return (step < max_step) ? it + step : first + (step - max_step);
}

// Returns the beginning of the lexicographical minimal rotation
// of the range [first, last) using the Duval's algorithm
template<class It>
It min_cyclic_rotation(It first, It last)
{
	assert(first != last);

	auto min_first = first;		   // beginning of the min. rotation
	auto it_first = min_first + 1; // beginning of the min. rotation candidate
	std::size_t offset = 0;

	const auto n = static_cast<size_t>(last - first);
	while (true)
	{
		assert(min_first < it_first);

		const auto min = cyclic_advance(min_first, first, last, offset);
		const auto it = cyclic_advance(it_first, first, last, offset);

		if (*min == *it)
		{
			if (++offset == n)
				break;
			continue;
		}

		if (*min > *it)
		{
			std::swap(min_first, it_first);

			assert(it_first < last - offset);
			it_first += offset + 1;
			it_first = std::max(it_first, min_first + 1);
		}
		else
		{
			if (it_first >= last - offset - 1)
				break;
			it_first += offset + 1;
		}

		offset = 0;
	}

	return min_first;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_ln(str_);
	}

	virtual void solve(unsigned int) override
	{
		std::unordered_set<Circular_view<std::string::const_iterator>> set;

		for (auto first = str_.begin(); first < str_.end(); ++first)
			for (auto last = first + 1; last <= str_.end(); ++last)
			{
				const auto start = min_cyclic_rotation(first, last);
				set.emplace(first, start, last);
			}

		write_ln(set.size());
	}

private:
	std::string str_;
};

MAIN

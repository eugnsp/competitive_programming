/*********************************************************************
Updating a dictionary
---------------------
UVa ID: 125 04

In this problem, a dictionary is collection of key-value pairs, where
keys are lower-case letters, andvalues are non-negative integers.
Given an old dictionary and a new dictionary, find out what were
changed. Each dictionary is formatting as follows:
	{key:value,key:value,...,key:value}
Each key is a string of lower-case letters, and each value is a
non-negative integer without leading zeros or prefix "+"". Each key
will appear at most once, but keys can appear in any order.

Input
-----
The first line contains the number of test cases T (T <= 1000). Each
test case contains two lines. The first line contains the old
dictionary, and the second line contains the new dictionary. Each
line will contain at most 100 characters and will not contain any
whitespace characters. Both dictionaries could be empty.

Output
------
For each test case, print the changes, formatted as follows:
 * First, if there are any new keys, print "+"" and then the new keys
   in increasing order (lexicographically), separated by commas.
 * Second, if there are any removed keys, print "-"" and then the
   removed keys in increasing order, separated by commas.
 * Last, if there are any keys with changed value, print "*"" and then
   these keys in increasing order, separated by commas.
If the two dictionaries are identical, print "No changes" instead.
Print a blank line after each test case.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <string>
#include <utility>
#include <vector>

// Partitions the given range and returns the iterator to the partition point
template<class It>
It partition(const It first, It last)
{
	assert(first != last);

	--last;
	const auto& pivot = *last;

	auto left = first;
	for (auto right = first; right != last; ++right)
	{
		// Invariants at this point:
		//  1. `*it <= pivot`  for  `it` in `[first, left)`
		//  2. `*it > pivot`   for  `it` in `[left, right)`
		//  3. `*it = pivot`   for  `it = last`
		if (!(*right > pivot))
			std::iter_swap(left++, right);
	}

	std::iter_swap(left, last);
	return left;
}

// Sorts the given range
template<class It>
void quick_sort(const It first, const It last)
{
	if (last - first <= 1)
		return;

	const auto p = partition(first, last);
	quick_sort(first, p);
	quick_sort(p, last);
}

using Entry = std::pair<std::string, std::string>;
using Dictionary = std::vector<Entry>;

void read_dictionary(Dictionary& dictionary)
{
	dictionary.clear();

	char ch;
	read(ch);
	assert(ch == '{');

	std::string key, value;

	bool dest = true;
	while (read(ch))
	{
		if (ch == ',' || ch == '}')
		{
			if (!key.empty() && !value.empty())
				dictionary.emplace_back(std::move(key), std::move(value));
			if (ch == '}')
				break;

			key.clear();
			value.clear();
			dest = true;
		}
		else if (ch == ':')
			dest = !dest;
		else
			(dest ? key : value) += ch;
	}
}

struct Diff
{
	std::vector<std::string> new_keys;
	std::vector<std::string> removed_keys;
	std::vector<std::string> changed_keys;

	bool is_empty() const
	{
		return new_keys.empty() && removed_keys.empty() && changed_keys.empty();
	}
};

Diff dictionary_diff(Dictionary& old_dict, Dictionary& new_dict)
{
	Diff diff;

	quick_sort(old_dict.begin(), old_dict.end());
	quick_sort(new_dict.begin(), new_dict.end());

	auto it_old = old_dict.begin();
	auto it_new = new_dict.begin();
	while (it_old != old_dict.end() && it_new != new_dict.end())
	{
		if (it_old->first < it_new->first)
		{
			diff.removed_keys.push_back(it_old->first);
			++it_old;
		}
		else if (it_new->first < it_old->first)
		{
			diff.new_keys.push_back(it_new->first);
			++it_new;
		}
		else
		{
			if (it_old->second != it_new->second)
				diff.changed_keys.push_back(it_old->first);
			++it_old;
			++it_new;
		}
	}

	std::for_each(it_old, old_dict.end(),
		[&diff](Entry& entry) { diff.removed_keys.push_back(entry.first); });
	std::for_each(
		it_new, new_dict.end(), [&diff](Entry& entry) { diff.new_keys.push_back(entry.first); });

	return diff;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_dictionary(old_dict_);
		read_dictionary(new_dict_);
	}

	virtual void solve(unsigned int) override
	{
		const auto diff = dictionary_diff(old_dict_, new_dict_);
		if (!diff.is_empty())
		{
			const auto list_keys = [](char prefix, const auto& keys) {
				if (!keys.empty())
				{
					write(prefix);
					write_vec(keys, ',');
					write_ln();
				}
			};

			list_keys('+', diff.new_keys);
			list_keys('-', diff.removed_keys);
			list_keys('*', diff.changed_keys);
		}
		else
			write_ln("No changes");

		write_ln();
	}

private:
	Dictionary old_dict_;
	Dictionary new_dict_;
};

MAIN

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
#include <vector>
#include <utility>

using Entry = std::pair<std::string, std::string>;
using Dictionary = std::vector<Entry>;

// Partitions the given range and returns
// the iterator to the partition point
template<class It>
It partition(It first, It last)
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
void quick_sort(It first, It last)
{
	if (last - first <= 1)
		return;

	auto p = partition(first, last);
	quick_sort(first, p);
	quick_sort(p, last);
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		old_dictionary_.clear();
		new_dictionary_.clear();

		read_dictionary(old_dictionary_);
		read_dictionary(new_dictionary_);
	}

	static void read_dictionary(Dictionary& dictionary)
	{
		char ch;
		read(ch);
		assert(ch == '{');

		std::string key;
		std::string value;

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
			} else if (ch == ':')
				dest = !dest;
			else
				(dest ? key : value) += ch;
		}
	}

	virtual void solve(unsigned int) override
	{
		quick_sort(old_dictionary_.begin(), old_dictionary_.end());
		quick_sort(new_dictionary_.begin(), new_dictionary_.end());

		std::vector<std::string> new_keys, removed_keys, changed_keys;

		auto it_old = old_dictionary_.begin();
		auto it_new = new_dictionary_.begin();
		while (it_old != old_dictionary_.end() && it_new != new_dictionary_.end())
		{
			if (it_old->first < it_new->first)
			{
				removed_keys.push_back(std::move(it_old->first));
				++it_old;
			}
			else if (it_new->first < it_old->first)
			{
				new_keys.push_back(std::move(it_new->first));
				++it_new;
			}
			else
			{
				if (it_old->second != it_new->second)
					changed_keys.push_back(std::move(it_old->first));
				++it_old;
				++it_new;
			}
		}

		std::for_each(it_old, old_dictionary_.end(), [&removed_keys](Entry& entry)
			{ removed_keys.push_back(std::move(entry.first)); });
		std::for_each(it_new, new_dictionary_.end(), [&new_keys](Entry& entry)
			{ new_keys.push_back(std::move(entry.first)); });

		if (new_keys.empty() && removed_keys.empty() && changed_keys.empty())
			write_ln("No changes");
		else
		{
			list_keys('+', new_keys);
			list_keys('-', removed_keys);
			list_keys('*', changed_keys);
		}

		write_ln();
	}

	static void list_keys(char prefix, const std::vector<std::string>& keys)
	{
		if (keys.empty())
			return;

		write(prefix);
		write_vec(keys, ',');
		write_ln();
	}

private:
	Dictionary old_dictionary_;
	Dictionary new_dictionary_;
};

MAIN(CP)

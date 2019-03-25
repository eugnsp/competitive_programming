/*********************************************************************
Word transformation
-------------------
UVa ID: 004 29

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <queue>
#include <string>
#include <vector>

using Size = unsigned int;
using Word = std::string;
using Dictionary = std::vector<Word>;

constexpr auto max_size = static_cast<Size>(-1);

bool compare_by_length(const Word& word1, const Word& word2)
{
	return word1.length() < word2.length();
}

// Returns true if two words are different in a single character only
bool is_one_char_mismatch(const Word& word1, const Word& word2)
{
	assert(word1.length() == word2.length());

	bool mismatch = false;
	for (auto it1 = word1.begin(), it2 = word2.begin(); it1 != word1.end(); ++it1, ++it2)
		if (*it1 != *it2)
		{
			if (mismatch)
				return false;
			mismatch = true;
		}

	return mismatch;
}

// Returns the length of the shortest "path" in the dictionary
// using the breadth-first search
Size shortest_path_length(const Dictionary& dict, const Word& first, const Word& last)
{
	assert(first.length() == last.length());
	assert(std::is_sorted(dict.begin(), dict.end(), compare_by_length));

	if (first == last)
		return 0;

	// Part of the dictionary with words of the same length as (first) and (last)
	const auto small_dict = std::equal_range(dict.begin(), dict.end(), first, compare_by_length);

	const auto small_dict_size = small_dict.second - small_dict.first;
	std::vector<Size> lengths(small_dict_size, max_size);
	std::queue<Dictionary::const_iterator> queue;

	const auto first_pos = std::find(small_dict.first, small_dict.second, first);
	assert(first_pos != small_dict.second);

	lengths[first_pos - small_dict.first] = 0;
	queue.push(first_pos);

	while (!queue.empty())
	{
		const auto word = queue.front();
		queue.pop();

		for (auto it = small_dict.first; it != small_dict.second; ++it)
		{
			const auto i = it - small_dict.first;
			if (lengths[i] == max_size && is_one_char_mismatch(*it, *word))
			{
				const auto w = word - small_dict.first;
				lengths[i] = lengths[w] + 1;

				if (*it == last)
					return lengths[i];

				queue.push(it);
			}
		}
	}

	return max_size;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::string str;

		// CHECK
		dictionary_.clear();
		while (read_ln(str) && str != "*")
			if (!str.empty())
				dictionary_.push_back(str);

		queries_.clear();
		while (read_ln(str))
		{
			const auto space = str.find(' ');
			queries_.push_back({str.substr(0, space), str.substr(space + 1)});
		}

		std::sort(dictionary_.begin(), dictionary_.end(), compare_by_length);
	}

	virtual void solve(unsigned int i_case) override
	{
		if (i_case > 1)
			write_ln();

		for (auto& q : queries_)
			write_ln(
				q.first, ' ', q.second, ' ', shortest_path_length(dictionary_, q.first, q.second));
	}

private:
	Dictionary dictionary_;
	std::vector<std::pair<Word, Word>> queries_;
};



/*********************************************************************
Babelfish
---------
UVa ID: 102 82

You have just moved from Waterloo to a big city. The people here speak
an incomprehensible dialect of a foreign language. Fortunately, you 
have a dictionary to help you understand them.

Input
-----
Input consists of up to 100,000 dictionary entries, followed by a 
blank line, followed by a message of up to 100,000 words. Each
dictionary entry is a line containing an English word, followed by a
space and a foreign language word. No foreign word appears more than
once in the dictionary. The message is a sequence of words in the 
foreign language, one word on each line. Each word in the input is a 
sequence of at most 10 lowercase letters.

Output
------
Output is the message translated to English, one word per line. 
Foreign words not in the dictionary should be translated as 'eh'.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <string>
#include <vector>
#include <utility>

template<class Key, class Value>
class Hash_table
{
private:
	using Pair = std::pair<Key, Value>;

public:
	Hash_table(std::size_t size)
	{
		++size;
		size *= 1.5;
		table_.resize(size);
	}

	void insert(Pair pair)
	{
		const auto hash = std::hash<Key>{}(pair.first);
		const auto size = table_.size();
		
		auto pos = hash % size;
		while (true)
		{
			if (table_[pos].second.empty())
			{
				table_[pos] = std::move(pair);
				return;
			}

			++pos;
			if (pos == size)
				pos = 0;
		}
	}

	const Value* operator[](const Key& key) const
	{
		const auto hash = std::hash<Key>{}(key);
		const auto size = table_.size();
		
		auto pos = hash % size;
		while (true)
		{
			if (table_[pos].first == key)
				return &table_[pos].second;
			if (table_[pos].second.empty())
				return nullptr;

			++pos;
			if (pos == size)
				pos = 0;
		}
	}

private:


private:
	std::vector<Pair> table_;
};

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::string str;

		dictionary_.clear();
		words_.clear();

		while (read_ln(str))
			dictionary_.push_back(split(std::move(str)));

		while (read_ln(str))
			words_.push_back(std::move(str));

		return !dictionary_.empty() && !words_.empty();
	}

	virtual void solve(unsigned int) override
	{
		Hash_table<std::string, std::string> table(dictionary_.size());
		for (auto& words : dictionary_)
			table.insert(swap_words(std::move(words)));

		for (auto& word : words_)
		{
			auto translated = table[word];
			if (translated)
				write_ln(*translated);
			else
				write_ln("eh");
		}
	}

	static std::pair<std::string, std::string> split(std::string str)
	{
		const auto space_pos = std::find(str.begin(), str.end(), ' ');
		assert(space_pos != str.end());

		std::string second_word(space_pos + 1, str.end());
		str.erase(space_pos, str.end());

		return {std::move(str), std::move(second_word)};
	}

	static std::pair<std::string, std::string> swap_words(std::pair<std::string, std::string> p)
	{
		return {std::move(p.second), std::move(p.first)};
	}

private:
	std::vector<std::pair<std::string, std::string>> dictionary_;
	std::vector<std::string> words_;
};

MAIN(CP)

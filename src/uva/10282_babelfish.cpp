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

using Word = std::string;
using Words_pair = std::pair<Word, Word>;

// An open addressing hash table with quadratic probing
class Hash_table
{
private:
	using Key = Word;
	using Value = Word;
	using Pair = std::pair<Key, Value>;

public:
	Hash_table(std::size_t size)
	{
		// Get the next power of two
		while (size & (size - 1))
			++size;

		table_.resize(size);
	}

	void insert(Pair pair)
	{
		assert(!pair.second.empty());

		const auto size = table_.size();
		auto pos = hash(pair.first);
		for (std::size_t i = 1; i <= size; ++i)
		{
			if (table_[pos].second.empty())
			{
				table_[pos] = std::move(pair);
				return;
			}

			pos = (pos + i) % size;
		}

		assert(false);
	}

	const Value* operator[](const Key& key) const
	{
		const auto size = table_.size();
		auto pos = hash(key);
		for (std::size_t i = 1; i <= size; ++i)
		{
			if (table_[pos].first == key)
				return &table_[pos].second;
			if (table_[pos].second.empty())
				return nullptr;

			pos = (pos + i) % size;
		}

		assert(false);
		return nullptr;
	}

private:
	std::size_t hash(const Key& key) const
	{
		return std::hash<Key>{}(key) % table_.size();
	}

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
		Hash_table table(dictionary_.size());
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

	static Words_pair split(std::string str)
	{
		const auto space_pos = std::find(str.begin(), str.end(), ' ');
		assert(space_pos != str.end());

		std::string second_word(space_pos + 1, str.end());
		str.erase(space_pos, str.end());

		return {std::move(str), std::move(second_word)};
	}

	static Words_pair swap_words(Words_pair p)
	{
		return {std::move(p.second), std::move(p.first)};
	}

private:
	std::vector<Words_pair> dictionary_;
	std::vector<Word> words_;
};



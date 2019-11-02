/*********************************************************************
Restore an alphabet from a dictionary
-------------------------------------

Find the order of characters in the language for the gviven sorted
dictionary.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cstddef>
#include <iterator>
#include <string>
#include <unordered_set>
#include <utility>
#include <vector>

struct Node
{
	std::size_t in_degree = 0;
	std::unordered_set<std::size_t> edges;
};

template<class It, class Fn>
void for_each_pair(It first, It last, Fn&& fn)
{
	if (first == last)
		return;
	auto next = std::next(first);
	while (next != last)
		fn(*first++, *next++);
	return;
}

std::string restore_alphabet_by_dictionary(const std::vector<std::string>& words,
										   std::size_t n_letters)
{
	std::vector<Node> letters_graph(n_letters);

	for_each_pair(words.begin(), words.end(),
		[&letters_graph](const std::string word1, const std::string word2)
		{
			auto it1 = word1.begin();
			auto it2 = word2.begin();
			while (it1 != word1.end() && it2 != word2.end() && *it1 == *it2)
				++it1, ++it2;

			if (it1 == word1.end() || it2 == word2.end())
				return;

			const auto from = static_cast<std::size_t>(*it1 - 'a');
			const auto to = static_cast<std::size_t>(*it2 - 'a');

			const bool was_inserted = letters_graph[from].edges.insert(to).second;
			if (was_inserted)
				++letters_graph[to].in_degree;
		});

	std::vector<std::size_t> zero_in_degrees_letters;
	for (std::size_t i = 0; i < letters_graph.size(); ++i)
		if (letters_graph[i].in_degree == 0)
			zero_in_degrees_letters.push_back(i);

	std::string alphabet;
	while (!zero_in_degrees_letters.empty())
	{
		const auto letter = zero_in_degrees_letters.back();
		zero_in_degrees_letters.pop_back();

		alphabet.push_back(static_cast<char>('a' + letter));
		for (auto next : letters_graph[letter].edges)
			if (letters_graph[next].in_degree > 0 && --letters_graph[next].in_degree == 0)
				zero_in_degrees_letters.push_back(next);
	}

	return alphabet;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t n_words;
		read(n_words, n_letters_);

		words_.clear();
		read_vec(n_words, words_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(restore_alphabet_by_dictionary(words_, n_letters_));
	}

private:
	std::size_t n_letters_;
	std::vector<std::string> words_;
};

MAIN

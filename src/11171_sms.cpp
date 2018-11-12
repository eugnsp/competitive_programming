/*********************************************************************
Largest sum game
----------------
UVa ID: 111 71

When typing SMS messages on a mobile phone, each of the ten digit 
buttons represent several alphabetic characters. On my phone (an 
ancient Ericsson T65, in case anyone was wondering), I have the 
following mapping (1 is used for space, and 0 for some common 
non-alphabetic symbols): 2 -> ABC, 3 -> DEF, 4 -> GHI, 5 -> JKL, 
6 -> MNO, 7 -> PQRS, 8 -> TUV, 9 -> WXYZ.

As you've probably experienced, this makes the typing quite 
cumbersome. The phones usually try to compensate this by making use 
of a dictionary basically, the idea is that there will typically be 
relatively few actual words having the same button combination. The 
way this works is that when you have typed a certain digit sequence,
you can cycle through the words in the dictionary that map to this 
digit sequence using the "up" and "down" buttons. Pressing "up" gives
you the next word, and pressing "down" gives you the previous word. 
Words are ordered by how common they are, most common words first and
least common words last. This wraps, so that pressing "up" at the last
word gives you the first word and similarly for "down". Initially 
after having pressed a digit sequence, you will get the  rst (most 
common) word that maps to this sequence. This usually works quite 
well, but if you're trying to type a word that does not exist in the
dictionary, you have to write it by separating it into several parts,
where each part is a word in the dictionary. In order to start writing
a new part, you have to press the "right" button on the keypad. 
Obviously, the number of keys needed to type a word depends on how 
(and if) we divide it into parts. Now, I would like to know how to 
type a word (that may or may not be from the dictionary) using as few
key presses as possible (it's not that I'm lazy, I just want to 
decrease the wear and tear of my keypad).

Input
-----
The input consists of several data sets (at most 5), terminated by a 
line containing a single 0. Each data set begins with an integer 
1 <= N <= 10'000 giving the size of the dictionary, followed by N 
lines, giving the words of the dictionary from most common to least 
common. Words consist solely of lower case 'a'-'z' and are at most 10
characters long. Then follows an integer Q >= 1 giving the number of
words to type. This is followed by Q lines, each containing a nonempty
word to type. It will always be possible to type the given words using
the given dictionary. The total length of all Q words to type will be
at most 250'000.

Output
------
For each query, output a line containing any optimal keypress solution
in the following format:
* For pressing any of the digits 2-9, simply output that digit.
* For pressing right, output 'R'.
* For pressing up or down x > 0 times, output 'U(x)' or 'D(x)',
  respectively.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <map>
#include <memory>
#include <string>
#include <vector>

using Word = std::string;
using Words = std::vector<Word>;

class Sms
{
private:
	static constexpr auto invalid_n_keys = static_cast<std::size_t>(-1);

	struct Node
	{
		std::array<std::unique_ptr<Node>, 26> children;
		std::string key_sequence;

		union
		{
			std::size_t n_keys = 0;
			std::size_t same_digits_list_index;
		};

		auto& child(char ch)
		{
			return children[letter_to_index(ch)];
		}

		auto& child(char ch) const
		{
			return children[letter_to_index(ch)];
		}
	};

	struct Memo_node
	{
		const Node* node_ptr = nullptr;
		std::size_t n_keys = invalid_n_keys;
		std::size_t word_length = 0;
	};

	using Memo = std::map<std::string::iterator, Memo_node>;

public:
	Sms(const Words& dictionary)
	{
		build_trie(dictionary);
	}

	std::string key_sequence(Word text) const
	{
		Memo memo;
		min_key_sequence(text.begin(), text.end(), memo);

		std::string key_sequence;
		for (auto it = text.begin(); ; key_sequence += 'R')
		{
			const auto& memo_node = memo.at(it);
			auto node = memo_node.node_ptr;
			assert(node != nullptr);

			key_sequence += node->key_sequence;
			it += memo_node.word_length;
			if (it == text.end())
				break;
		}

		return key_sequence;
	}

private:
	static std::size_t letter_to_index(char letter)
	{
		assert('a' <= letter && letter <= 'z');
		return static_cast<std::size_t>(letter - 'a');
	}

	static char letter_to_digit(char letter)
	{
		assert('a' <= letter && letter <= 'z');

		constexpr char l_to_d[] = {2, 2, 2, 3, 3, 3, 4, 4, 4,
			5, 5, 5, 6,	6, 6, 7, 7, 7, 7, 8, 8, 8, 9, 9, 9, 9};
		return '0' + l_to_d[letter_to_index(letter)];
	}

	static Word text_to_digits(Word text)
	{
		std::transform(text.begin(), text.end(),
			text.begin(), letter_to_digit);
		return text;
	}

	void build_trie(const Words& dictionary)
	{
		std::map<std::string, std::size_t> same_digits_list_index;
		std::vector<Node*> leaves;
		leaves.reserve(dictionary.size());

		for (auto& word : dictionary)
		{
			auto node = &dictionary_;
			for (auto ch : word)
			{
				auto& child = node->child(ch);
 				if (!child)
 					child.reset(new Node);
				node = child.get();
			}

			const auto digits = text_to_digits(word);
			node->same_digits_list_index = same_digits_list_index[digits]++;
			node->key_sequence = digits;

			leaves.push_back(node);
		}

		for (auto leaf : leaves)
		{
			const auto index = leaf->same_digits_list_index;
			if (index == 0)
				leaf->n_keys = leaf->key_sequence.length();
			else
			{
				const auto same_digits_list_size = same_digits_list_index[leaf->key_sequence];
				const auto inv_index = same_digits_list_size - index;
				const auto min_index = std::min(index, inv_index);
				leaf->n_keys = leaf->key_sequence.length() + min_index;
				leaf->key_sequence += (index <= inv_index ? 'U' : 'D') +
					('(' + std::to_string(min_index) + ')');
			}
		}
	}

	std::size_t min_key_sequence(std::string::iterator first,
		std::string::iterator last, Memo& memo) const
	{
		if (memo.count(first) > 0)
			return memo.at(first).n_keys;

		auto& memo_node = memo[first];
		Memo_node min_node;

		auto node = &dictionary_;
		for (std::size_t word_length = 1; first != last; ++first, ++word_length)
		{
			const auto& child = node->child(*first);
			if (!child)
				break;

			node = child.get();
			if (node->n_keys != 0)		// Found a word
			{
				auto n_keys = (first + 1 == last) ? 0 :
					min_key_sequence(first + 1, last, memo);
				if (n_keys == invalid_n_keys)
					continue;

				n_keys += node->n_keys + 1;
				if (n_keys < min_node.n_keys)
					min_node = Memo_node{node, n_keys, word_length};
			}
		}

		memo_node = min_node;
		return min_node.n_keys;
	}

private:
	Node dictionary_;
};

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_size_vec(dictionary_) && read_size_vec(texts_);
	}

	virtual void solve(unsigned int) override
	{
		Sms sms(dictionary_);
 		for (auto& text : texts_)
 			write_ln(sms.key_sequence(text));
	}

private:
	Words dictionary_;
	Words texts_;
};

MAIN(CP)

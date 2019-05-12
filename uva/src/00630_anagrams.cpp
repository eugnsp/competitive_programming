/*********************************************************************
Anagrams (II)
-------------
UVa ID: 006 30

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iomanip>
#include <string>
#include <vector>

bool is_anagram(std::string str1, std::string str2)
{
	if (str1.length() != str2.length())
		return false;

	std::sort(str1.begin(), str1.end());
	std::sort(str2.begin(), str2.end());

	return str1 == str2;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(words_);

		std::string test_word;

		test_words_.clear();
		while (read(test_word) && test_word != "END")
			test_words_.push_back(test_word);
	}

	virtual void solve(unsigned int i_case) override
	{
		if (i_case > 1)
			write_ln();

		for (auto& test_word : test_words_)
		{
			write_ln("Anagrams for: ", test_word);

			std::size_t i = 0;
			for (auto& word : words_)
				if (is_anagram(test_word, word))
					write_ln(std::setw(3), ++i, ") ", word);

			if (i == 0)
				write_ln("No anagrams for: ", test_word);
		}
	}

private:
	std::vector<std::string> words_;
	std::vector<std::string> test_words_;
};

MAIN


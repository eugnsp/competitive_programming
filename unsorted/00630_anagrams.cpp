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
#include <string>
#include <iomanip>
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
	virtual void read_input(std::istream& in) override
	{
		std::size_t n_words;
		in >> n_words;
		assert(n_words < 1000);

		words_.resize(n_words);
		for (auto& w : words_)
			in >> w;

		test_words_.clear();
		std::string test_word;
		while (true)
		{
			in >> test_word;
			if (test_word == "END")
				break;
			test_words_.push_back(test_word);
		}
	}

	virtual void solve(std::ostream& out, unsigned int i_case) const override
	{
		if (i_case > 0)
			out << '\n';

		for (auto& test_word : test_words_)
		{
			out << "Anagrams for: " << test_word << '\n';

			std::size_t i = 0;
			for (auto& word : words_)
				if (is_anagram(test_word, word))
					out << std::setw(3) << ++i << ") " << word << '\n';

			if (i == 0)
				out << "No anagrams for: " << test_word << '\n';
		}
	}

private:
	std::vector<std::string> words_;
	std::vector<std::string> test_words_;
};

int main()
{
	CP p;
	return p.run();
}

/*********************************************************************
Anagrams
--------
UVa ID: 004 54

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

struct Phrase
{
	std::string str;
	std::string key;

	Phrase(const std::string& s)
		: str(s), key(s)
	{
		remove_blanks(key);
	}

private:
	static void remove_blanks(std::string& str)
	{
		const auto is_space = [](char c) { return c == ' '; };
		const auto last = std::remove_if(str.begin(), str.end(), is_space);
		str.erase(last, str.end());
	}
};

bool is_anagram(const std::string& str1, const std::string& str2)
{
	if (str1.length() != str2.length())
		return false;

	auto str1_c = str1;
	auto str2_c = str2;

	std::sort(str1_c.begin(), str1_c.end());
	std::sort(str2_c.begin(), str2_c.end());

	return str1_c == str2_c;
}

class CP : public CP1
{
private:
	virtual void read_input(std::istream& in) override
	{
		phrases_.clear();
		
		std::string phrase;
		while (std::getline(in, phrase))
			if (phrase.empty())
			{
				if (!phrases_.empty())
					return;
			}
			else
				phrases_.emplace_back(phrase);

		assert(phrases_.size() <= 100);
	}

	virtual void solve(std::ostream& out, std::size_t i_case) const override
	{
		std::vector<Phrase> phrases(phrases_);
		std::sort(phrases.begin(), phrases.end(),
			[](const Phrase& p1, const Phrase& p2) { return p1.str < p2.str; });

		if (i_case > 0)
			out << '\n';

		for (auto p1 = phrases.begin(); p1 != phrases.end(); ++p1)
			for (auto p2 = p1 + 1; p2 != phrases.end(); ++p2)
				if (is_anagram(p1->key, p2->key))
					out << p1->str << " = " << p2->str << '\n';
	}

private:
	std::vector<Phrase> phrases_;
};

int main()
{
	CP p;
	return p.run();
}

/*********************************************************************
Phone list
----------
UVa ID: 113 62

Given a list of phone numbers, determine if it is consistent in the
sense that no number is the prefix of another. Let's say the phone
catalogue listed these numbers:
	Emergency 	911
	Alice 		97 625 999
	Bob 		91 125 426
In this case, it's not possible to call Bob, because the central would
direct your call to the emergency line as soon as you had dialled the
first three digits of Bob's phone number. So this list would not be
consistent.

Input
-----
The first line of input gives a single integer, 1 <= t <= 40, the
number of test cases. Each test case starts with n, the number of
phone numbers, on a separate line, 1 <= n <= 10'000. Then follows n
lines with one unique phone number on each line. A phone number is a
sequence of at most ten digits.

Output
------
For each test case, output "YES" if the list is consistent, or "NO"
otherwise.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <array>
#include <cstddef>
#include <memory>
#include <string>
#include <vector>

class Trie
{
private:
	struct Node
	{
		std::array<std::unique_ptr<Node>, 10> children;
		bool is_terminal = false;
	};

public:
	template<class It>
	bool try_insert(It first, It last)
	{
		Node* node = &root_;

		while (first != last)
		{
			if (node->is_terminal)
				return false;

			auto& child = node->children[digit_to_index(*first++)];
			if (!child)
				child.reset(new Node);
			else if (first == last)
				return false;

			node = child.get();
		}

		node->is_terminal = true;
		return true;
	}

private:
	static std::size_t digit_to_index(char digit)
	{
		assert('0' <= digit && digit <= '9');
		return static_cast<std::size_t>(digit - '0');
	}

	Node root_;
};

template<class It>
bool is_prefix_consistent(It first, It last)
{
	for (Trie trie; first != last; ++first)
		if (!trie.try_insert(first->begin(), first->end()))
			return false;

	return true;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(phones_);
	}

	virtual void solve(unsigned int) override
	{
		const auto f = is_prefix_consistent(phones_.begin(), phones_.end());
		write_ln(f ? "YES" : "NO");
	}

private:
	std::vector<std::string> phones_;
};

MAIN

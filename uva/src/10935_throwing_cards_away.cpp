/*********************************************************************
Maximum sum
-----------
UVa ID: 109 35

Given is an ordered deck of n cards numbered 1 to n with card 1 at
the top and card n at the bottom. The following operation is performed
as long as there are at least two cards in the deck: throw away the
top card and move the card that is now on the top of the deck to the
bottom of the deck. Your task is to find the sequence of discarded
cards and the last, remaining card.

Input
-----
Each line of input (except the last) contains a number n <= 50. The
last line contains "0" and this line should not be processed.

Output
------
For each number from the input produce two lines ofoutput. The first
line presents the sequence of discarded cards, the second line reports
the last remaining card. No line will have leading or trailing spaces.
See the sample for the expected format.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "util.hpp"
#include <cassert>
#include <cstddef>
#include <utility>

template<class T>
class Queue
{
private:
	struct Node
	{
		T data;
		Node* next;
	};

public:
	~Queue()
	{
		while (!is_empty())
			pop();
	}

	void push(const T& data)
	{
		const auto new_node = new Node{data, nullptr};
		(!is_empty() ? front->next : back) = new_node;
		front = new_node;
	}

	T pop()
	{
		assert(!is_empty());

		auto data = std::move(back->data);
		delete exchange(back, back->next);

		return data;
	}

	bool is_empty() const
	{
		return back == nullptr;
	}

private:
	Node* front = nullptr;
	Node* back = nullptr;
};

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(n_) && n_ > 0;
	}

	virtual void solve(unsigned int) override
	{
		Queue<std::size_t> cards;
		for (std::size_t i = 1; i <= n_; ++i)
			cards.push(i);

		write("Discarded cards:");

		while (true)
		{
			const auto thrown_card = cards.pop();
			if (cards.is_empty())
			{
				write_ln();
				write_ln("Remaining card: ", thrown_card);
				break;
			}

			if (thrown_card != 1)
				write(',');
			write(' ', thrown_card);

			cards.push(cards.pop());
		}
	}

private:
	std::size_t n_;
};



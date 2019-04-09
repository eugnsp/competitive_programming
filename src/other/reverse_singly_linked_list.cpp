/*********************************************************************
Reverse a singly-linked list
----------------------------

Reverse the given singly-linked list.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "uptr_list.hpp"
#include <cstddef>
#include <memory>
#include <utility>

template<typename Node>
Node* unique_ptr_exchange(std::unique_ptr<Node>& value, Node* new_value)
{
	const auto old = value.release();
	value.reset(new_value);
	return old;
}

template<class Node>
void reverse(std::unique_ptr<Node>& head)
{
	Node* prev = nullptr;
	for (auto curr = head.release(); curr != nullptr;)
	{
		auto next = unique_ptr_exchange(curr->next, prev);
		prev = std::exchange(curr, next);
	}

	head.reset(prev);
}

using T = unsigned int;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t size;
		read(size);
		list_ = read_list<T>(size);
	}

	virtual void solve(unsigned int) override
	{
		reverse(list_);
		write_ln(list_);
	}

private:
	std::unique_ptr<Node<T>> list_;
};

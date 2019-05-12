/*********************************************************************
Reverse a singly-linked list
----------------------------

Reverse the given singly-linked list.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "uptr_list.hpp"
#include <cstddef>
#include <utility>

template<typename T>
Node<T>* unique_ptr_exchange(Node_ptr<T>& value, Node<T>* new_value)
{
	return std::exchange(value, Node_ptr<T>{new_value}).release();
}

template<typename T>
void reverse(Node_ptr<T>& head)
{
	Node<T>* prev = nullptr;
	for (auto curr = head.release(); curr != nullptr;)
	{
		auto next = unique_ptr_exchange(curr->next, prev);
		prev = std::exchange(curr, next);
	}

	head.reset(prev);
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t size;
		read(size);
		read_list(size, list_);
	}

	virtual void solve(unsigned int) override
	{
		reverse(list_);
		write_ln(list_);
	}

private:
	Node_ptr<unsigned int> list_;
};

MAIN

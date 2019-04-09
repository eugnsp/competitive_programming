/*********************************************************************
Rotate a singly-linked list
---------------------------

Rotate the given singly-linked list.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "uptr_list.hpp"
#include <cassert>
#include <cstddef>
#include <memory>
#include <utility>

template<class Node>
std::size_t list_size(Node* head)
{
	std::size_t size = 0;
	while (head != nullptr)
	{
		++size;
		head = head->next;
	}

	return size;
}

template<class Node>
void rotate(std::unique_ptr<Node>& head, std::size_t offset)
{
	if (offset == 0)
		return;

	auto node = head.get();
	while (--offset > 0)
		node = node->next.get();
	std::swap(head, node->next);

	const auto tail = std::exchange(node, head.get());
	while (node->next)
	 	node = node->next.get();
	std::swap(node->next, tail->next);
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

		read(offset_);
		assert(offset_ < size);
	}

	virtual void solve(unsigned int) override
	{
		rotate(list_, offset_);
		write_ln(list_);
	}

private:
	std::unique_ptr<Node<T>> list_;
	std::size_t offset_;
};

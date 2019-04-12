/*********************************************************************
Merge two singly-linked lists
-----------------------------

Merge the two given singly-linked lists.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "uptr_list.hpp"
#include <cstddef>
#include <utility>

template<typename T>
Node_ptr<T> exchange_next(Node_ptr<T>& node)
{
	return std::exchange(node, std::move(node->next));
}

// Stably merges two sorted lists into the first one
template<typename T>
Node_ptr<T> merge(Node_ptr<T> head1, Node_ptr<T> head2)
{
	if (!head2)
		return head1;
	if (!head1)
		return head2;

	auto p1 = std::move(head1);
	auto p2 = std::move(head2);
	auto head = (p2->data < p1->data) ? exchange_next(p2) : exchange_next(p1);

	auto tail = &head;
	while (p1 && p2)
	{
		(*tail)->next = (p2->data < p1->data) ? exchange_next(p2) : exchange_next(p1);
		tail = &(*tail)->next;
	}

	if (p1)
		(*tail)->next = std::move(p1);
	else if (p2)
		(*tail)->next = std::move(p2);

	return head;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t size1, size2;
		read(size1, size2);
		read_list(size1, list1_);
		read_list(size2, list2_);
	}

	virtual void solve(unsigned int) override
	{
		list1_ = merge(std::move(list1_), std::move(list2_));
		write_ln(list1_);
	}

private:
	Node_ptr<unsigned int> list1_;
	Node_ptr<unsigned int> list2_;
};

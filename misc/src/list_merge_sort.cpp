/*********************************************************************
Merge sort a singly-linked list
-------------------------------

Sort the given singly-linked list using merge sort.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "uptr_list.hpp"
#include <cstddef>
#include <utility>

// Splits the list in the middle, returns the pointer to the second half
template<typename T>
Node_ptr<T> middle_split(Node_ptr<T>& head)
{
	auto slow = &head;
	auto fast = slow;

	while (*fast)
	{
		fast = &(*fast)->next;
		if (!*fast)
			break;
		slow = &(*slow)->next;
		fast = &(*fast)->next;
	}

	return std::move(*slow);
}

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

template<typename T>
void sort(Node_ptr<T>& head)
{
	if (!head || !head->next)
		return;

	auto mid = middle_split(head);
	sort(head);
	sort(mid);
	head = merge(std::move(head), std::move(mid));
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
		sort(list_);
		write_ln(list_);
	}

private:
	std::unique_ptr<Node<unsigned int>> list_;
};

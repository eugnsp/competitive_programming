/*********************************************************************
Connection point in Y-shaped linked lists
-----------------------------------------

Find the connection point of the two given linked lists that join
at some point, forming a Y-shaped structure.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "list.hpp"
#include <cassert>
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
void advance(Node*& head, std::size_t n = 1)
{
	while (n-- > 0)
	{
		assert(head);
		head = head->next;
	}
}

template<class Node>
Node* connection_point(Node* head1, Node* head2)
{
	const auto size1 = list_size(head1);
	const auto size2 = list_size(head2);

	if (size1 > size2)
		advance(head1, size1 - size2);
	else if (size2 > size1)
		advance(head2, size2 - size1);

	while (true)
	{
		if (head1 == head2)
			return head1;
		advance(head1);
		advance(head2);
	}
}

using T = unsigned int;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t size1, size2, size3;
		read(size1, size2, size3);

		auto list1 = read_list<T>(size1);
		auto list2 = read_list<T>(size2);
		const auto list3 = read_list<T>(size3);

		head1_ = (list1.first != nullptr) ? list1.first : list3.first;
		head2_ = (list2.first != nullptr) ? list2.first : list3.first;
		if (list1.second)
			list1.second->next = list3.first;
		if (list2.second)
			list2.second->next = list3.first;
	}

	virtual void solve(unsigned int) override
	{
		const auto y_point = connection_point(head1_, head2_);
		if (y_point != nullptr)
			write_ln(y_point->key);
		else
			write_ln(-1);
	}

private:
	Node<T>* head1_;
	Node<T>* head2_;
};

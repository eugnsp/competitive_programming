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
#include <cstddef>
#include <utility>

template<typename T>
void advance(Node<T>*& head, std::size_t n = 1)
{
	while (n-- > 0)
	{
		assert(head);
		head = head->next;
	}
}

template<typename T>
std::size_t list_size(Node<T>* head)
{
	std::size_t size = 0;
	while (head != nullptr)
	{
		++size;
		advance(head);
	}

	return size;
}

// Returns the point at which two linked lists join,
// returns nullptr if they do not join
template<typename T>
Node<T>* connection_point(Node<T>* head1, Node<T>* head2)
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

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t size1, size2, size3;
		read(size1, size2, size3);

		const auto tail1 = read_list(size1, head1_);
		const auto tail2 = read_list(size2, head2_);

		decltype(head1_) list3;
		read_list(size3, list3);

		(head1_ != nullptr ? tail1->next : head1_) = list3;
		(head2_ != nullptr ? tail2->next : head2_) = list3;
	}

	virtual void solve(unsigned int) override
	{
		const auto y_point = connection_point(head1_, head2_);
		if (y_point != nullptr)
			write_ln(y_point->data);
		else
			write_ln(-1);
	}

private:
	Node<unsigned int>* head1_;
	Node<unsigned int>* head2_;
};

MAIN

/*********************************************************************
Check if a singly-linked list is a palindrome
---------------------------------------------

Check if the given singly-linked list is a palindrome.

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
Node_ptr<T>& middle(Node_ptr<T>& head)
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

	return *slow;
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

template<typename T>
bool is_palindrome(Node_ptr<T>& head)
{
	auto& mid = middle(head);
	reverse(mid);

	auto p1 = head.get();
	auto p2 = mid.get();

	bool is_palindrome = true;
	while (p2 != nullptr)
	{
		if (p1->data != p2->data)
		{
			is_palindrome = false;
			break;
		}
		p1 = p1->next.get();
		p2 = p2->next.get();
	}

	reverse(mid);
	return is_palindrome;
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
		write_ln(is_palindrome(list_) ? 1 : 0);
	}

private:
	Node_ptr<unsigned int> list_;
};

MAIN

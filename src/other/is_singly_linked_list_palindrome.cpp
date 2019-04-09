/*********************************************************************
Check if a singly-linked list is a palindrome
---------------------------------------------

Check if the given singly-linked list is a palindrome.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "uptr_list.hpp"
#include <cstddef>
#include <memory>

template<typename Node>
Node* unique_ptr_exchange(std::unique_ptr<Node>& value, Node* new_value)
{
	const auto old = value.release();
	value.reset(new_value);
	return old;
}

template<class Node>
std::unique_ptr<Node>& middle(std::unique_ptr<Node>& head)
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

template<class Node>
bool is_palindrome(std::unique_ptr<Node>& head)
{
	auto& mid = middle(head);
	reverse(mid);

	auto p1 = head.get();
	auto p2 = mid.get();

	bool is_palindrome = true;
	while (p2 != nullptr)
	{
		if (p1->key != p2->key)
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
		write_ln(is_palindrome(list_) ? 1 : 0);
	}

private:
	std::unique_ptr<Node<T>> list_;
};

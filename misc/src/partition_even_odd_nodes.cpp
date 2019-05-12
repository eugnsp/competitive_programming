/*********************************************************************
Partition even and odd nodes
----------------------------

Relink the given singly-linked list such that all even-valued nodes
come before all odd-valued ones preserving their relative order.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <memory>
#include <utility>

template<typename T>
bool is_even(T value)
{
	return (value % 2) == 0;
}

template<typename T>
struct Node
{
	T data;
	Node* next = nullptr;

	Node(T data) : data(std::move(data))
	{}
};

template<typename T>
void even_odd_partition(Node<T>*& list_root)
{
	Node<T>* even_root = nullptr;
	Node<T>* odd_root = nullptr;

	Node<T>* even_tail = nullptr;
	Node<T>* odd_tail = nullptr;

	for (auto node = list_root; node != nullptr; node = node->next)
	{
		auto& root = is_even(node->data) ? even_root : odd_root;
		auto& tail = is_even(node->data) ? even_tail : odd_tail;

		if (tail != nullptr)
			tail->next = node;
		else
			root = node;
		tail = node;
	}

	if (even_tail == nullptr || odd_tail == nullptr)
		return;

	even_tail->next = odd_root;
	odd_tail->next = nullptr;
	list_root = even_root;
}

template<class Node, class Fn>
void traverse(Node* root, Fn fn)
{
	while (root != nullptr)
		fn(std::exchange(root, root->next));
}

using T = unsigned int;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t size;
		read(size);

		auto node = &root_;
		while (size-- > 0)
		{
			T data;
			read(data);
			*node = new Node<T>(data);
			node = &(*node)->next;
		}
	}

	virtual void solve(unsigned int) override
	{
		even_odd_partition(root_);
		traverse(root_, [](const Node<T>* node) { write(node->data, ' '); });
		write_ln();

		traverse(root_, std::default_delete<Node<T>>{});
	}

private:
	Node<T>* root_;
};

MAIN

/*********************************************************************
XOR linked list
---------------

Implement insertion and traversal operations for a XOR linked list.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cstdint>
#include <memory>
#include <utility>
#include <vector>

template<typename T>
struct Node
{
	T data;
	Node* prev_xor_next;
};

template<typename T>
T* xor_ptr(T* const node1, T* const node2)
{
	auto ptr = reinterpret_cast<std::uintptr_t>(node1) ^ reinterpret_cast<std::uintptr_t>(node2);
	return reinterpret_cast<T*>(ptr);
}

template<typename T>
void insert(Node<T>*& head, const T& data)
{
	const auto new_ptr = new Node<T>{data, head};
	if (head)
		head->prev_xor_next = xor_ptr(head->prev_xor_next, new_ptr);

	head = new_ptr;
}

template<typename T, class Fn>
Node<T>* traverse(Node<T>* head, Fn fn)
{
	Node<T>* tail = nullptr;
	while (head)
	{
		const auto next = xor_ptr(head->prev_xor_next, tail);
		tail = std::exchange(head, next);
		fn(tail);
	}

	return tail;
}

using T = int;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(seq_);
	}

	virtual void solve(unsigned int) override
	{
		Node<T>* head = nullptr;
		for (T i : seq_)
			insert(head, i);

		const auto fn = [](const Node<T>* node) { write(node->data, ' '); };

		const auto tail = traverse(head, fn);
		write_ln();
		traverse(tail, fn);
		write_ln();

		traverse(head, std::default_delete<Node<T>>{});
	}

private:
	std::vector<T> seq_;
};

MAIN

// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include "io.hpp"
#include <cstddef>
#include <utility>

template<typename T>
struct Node
{
	const T data;
	Node* next = nullptr;

	explicit Node(T data) : data(std::move(data))
	{}
};

// Reads the lists, returns the pointer to the last element in the list
template<typename T>
Node<T>* read_list(std::size_t size, Node<T>*& head)
{
	head = nullptr;
	auto last = head;

	while (size-- > 0)
	{
		T data;
		read(data);
		const auto n = new Node(std::move(data));
		if (head != nullptr)
		{
			last->next = n;
			last = n;
		}
		else
			head = last = n;
	}

	return last;
}

template<typename T>
void write(const Node<T>* head)
{
	if (head == nullptr)
		return;

	write(head->data);
	while (head != nullptr)
	{
		write(' ', head->data);
		head = head->next;
	}
}

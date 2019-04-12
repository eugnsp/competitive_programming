// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include "io.hpp"
#include <cstddef>
#include <memory>
#include <utility>

template<typename T>
struct Node;

template<typename T>
using Node_ptr = std::unique_ptr<Node<T>>;

template<typename T>
struct Node
{
	const T data;
	Node_ptr<T> next;

	explicit Node(T data) : data(std::move(data))
	{}
};

template<typename T>
void read_list(std::size_t size, Node_ptr<T>& list)
{
	list.reset();
	Node<T>* tail;

	while (size-- > 0)
	{
		T data;
		read(data);
		if (list)
		{
			tail->next = std::make_unique<Node<T>>(std::move(data));
			tail = tail->next.get();
		}
		else
		{
			list = std::make_unique<Node<T>>(std::move(data));
			tail = list.get();
		}
	}
}

template<typename T>
void write(const Node_ptr<T>& head)
{
	if (!head)
		return;

	write(head->data);

	auto node = head->next.get();
	while (node != nullptr)
	{
		write(' ', node->data);
		node = node->next.get();
	}
}

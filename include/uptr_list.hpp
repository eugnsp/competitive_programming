#pragma once
#include "io.hpp"
#include <cstddef>
#include <memory>
#include <utility>

template<typename T>
struct Node
{
	const T key;
	std::unique_ptr<Node> next;

	explicit Node(T data) : key(std::move(data))
	{}
};

template<typename T>
std::unique_ptr<Node<T>> read_list(std::size_t size)
{
	std::unique_ptr<Node<T>> head;
	Node<T>* last = nullptr;

	while (size-- > 0)
	{
		T data;
		read(data);
		if (head)
		{
			last->next = std::make_unique<Node<T>>(std::move(data));
			last = last->next.get();
		}
		else
		{
			head = std::make_unique<Node<T>>(std::move(data));
			last = head.get();
		}
	}

	return head;
}

template<typename T>
void write(const std::unique_ptr<Node<T>>& head)
{
	if (!head)
		return;

	write(head->key);

	auto node = head->next.get();
	while (node != nullptr)
	{
		write(' ', node->key);
		node = node->next.get();
	}
}

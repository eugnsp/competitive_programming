#pragma once
#include "io.hpp"
#include <cstddef>
#include <utility>

template<typename T>
struct Node
{
	const T key;
	Node* next = nullptr;

	explicit Node(T data) : key(std::move(data))
	{}
};

template<typename T>
std::pair<Node<T>*, Node<T>*> read_list(std::size_t size)
{
	Node<T>* head = nullptr;
	Node<T>* last = nullptr;

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

	return {head, last};
}

template<typename T>
void write(const Node<T>* head)
{
	if (head == nullptr)
		return;

	write(head->key);
	while (head != nullptr)
	{
		write(' ', head->key);
		head = head->next;
	}
}

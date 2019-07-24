// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include "io.hpp"
#include <cstddef>
#include <memory>
#include <unordered_map>
#include <utility>

template<typename T>
struct Node;

template<typename T>
using Node_ptr = std::unique_ptr<Node<T>>;

template<typename T>
struct Node
{
	const T data;
	Node_ptr<T> left;
	Node_ptr<T> right;

	explicit Node(T data) : data(std::move(data))
	{}
};

template<typename T>
void read_tree(Node_ptr<T>& root)
{
	root.reset();
	std::unordered_map<T, Node_ptr<T>*> map;

	std::size_t n_edges;
	read(n_edges);
	for (std::size_t i = 0; i < n_edges; ++i)
	{
		T parent_data, child_data;
		char which;
		read(parent_data, child_data, which);
		const auto ptr = (which == 'L') ? &Node<T>::left : &Node<T>::right;

		if (const auto pos = map.find(parent_data); pos != map.end())
		{
			(**pos->second).*ptr = std::make_unique<Node<T>>(child_data);
			map.emplace(child_data, &((**pos->second).*ptr));
		}
		else
		{
			root = std::make_unique<Node<T>>(parent_data);
			(*root).*ptr = std::make_unique<Node<T>>(child_data);
			map.emplace(parent_data, &root);
			map.emplace(child_data, &((*root).*ptr));
		}
	}
}

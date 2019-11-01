/*********************************************************************
Oh, my trees!
-------------
UVa ID: 124 57

Pre-order traversal (root, left, right) prints out the nodes key by
visiting the root node then traversing the left subtree and then
traversing the right subtree. Post-order traversal (left, right, root)
prints out the left subtree first and then right subtree and finally
Given the pre-order traversal of a binary search tree, you task is
to find the post-order traversal of this tree.

Input
-----
The keys of all nodes of the input binary search tree are given
according to pre-order traversal. Each node has a key value which is a
positive integer less than 10^6. All values are given in separate lines
(one integer per line). You can assume that a binary search tree does
not contain more than 10'000 nodes and there are no duplicate nodes.

Output
------
The output contains the result of post-order traversal of the input
binary tree. Print out one key per line.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <cstddef>
#include <iterator>
#include <limits>
#include <memory>
#include <queue>
#include <utility>
#include <vector>

template<typename T>
struct Node;

template<typename T>
using Node_ptr = std::unique_ptr<Node<T>>;

template<typename T>
struct Node
{
	T key;
	Node_ptr<T> left;
	Node_ptr<T> right;

	explicit Node(T data) : key(std::move(data))
	{}
};

template<typename T>
struct Queue_node
{
	Node<T>* node;
	T min = std::numeric_limits<T>::min();
	T max = std::numeric_limits<T>::max();

	explicit Queue_node(Node<T>* node) : node(node)
	{}

	explicit Queue_node(Node<T>* node, T min, T max) : node(node), min(min), max(max)
	{}

	bool can_contain_in_subtree(const T& key) const
	{
		return min < key && key < max;
	}
};

template<class It, typename T = typename std::iterator_traits<It>::value_type>
Node_ptr<T> make_from_level_order(It first, It last)
{
	Node_ptr<T> root;
	if (first == last)
		return root;

	std::queue<Queue_node<T>> queue;
	root = std::make_unique<Node<T>>(*first++);
	queue.emplace(root.get());

	while (first != last)
	{
		assert(!queue.empty());
		auto top = queue.front();
		queue.pop();

		if (*first < top.node->key && top.can_contain_in_subtree(*first))
		{
			top.node->left = std::make_unique<Node<T>>(*first++);
			queue.emplace(top.node->left.get(), top.min, top.node->key);
		}
		if (first == last)
			break;

		if (*first > top.node->key && top.can_contain_in_subtree(*first))
		{
			top.node->right = std::make_unique<Node<T>>(*first++);
			queue.emplace(top.node->right.get(), top.node->key, top.max);
		}
	}

	return root;
}

template<typename T, class Fn>
void traverse_level_order(const Node_ptr<T>& root, Fn&& fn)
{
	if (!root)
		return;

	std::queue<Node<T>*> queue;
	queue.push(root.get());

	while (!queue.empty())
	{
		auto top = queue.front();
		queue.pop();

		if (top->left)
			queue.push(top->left.get());
		if (top->right)
			queue.push(top->right.get());

		fn(*top);
	}
}

using T = unsigned int;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t n_levels;
		read(n_levels);
		ignore_line();

		level_order_.clear();
		for (std::size_t i = 0; i < n_levels; ++i)
			read_vec_ln(level_order_);
	}

	virtual void solve(unsigned int) override
	{
		const auto tree = make_from_level_order(level_order_.begin(), level_order_.end());

		traverse_level_order(tree, [](const Node<T>& node) {
			write(node.key, ':');
			if (node.left)
				write(node.left->key);
			write('-');
			if (node.right)
				write(node.right->key);
			write_ln();
		});
	}

private:
	std::vector<T> level_order_;
};

MAIN

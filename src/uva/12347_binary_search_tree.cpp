/*********************************************************************
Binary search tree
------------------
UVa ID: 123 47

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
#include <iterator>
#include <memory>
#include <stack>
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

template<class It, typename T = typename std::iterator_traits<It>::value_type>
Node_ptr<T> make_from_pre_order(It first, It last)
{
	Node_ptr<T> root;
	if (first == last)
		return root;

	std::stack<Node<T>*> stack;

	root.reset(new Node<T>{*first++});
	stack.push(root.get());

	while (first != last)
	{
		Node<T>* last_popped = nullptr;

		// Invariant: all nodes in the stack has `key > *first`
		while (!stack.empty() && stack.top()->key < *first)
		{
			last_popped = stack.top();
			stack.pop();
		}

		auto& node = last_popped ? last_popped->right : stack.top()->left;
		assert(!node);
		node.reset(new Node<T>{*first++});
		stack.push(node.get());
	}

	return root;
}

template<typename T, class Fn>
void traverse_post_order(const Node_ptr<T>& root, Fn&& fn)
{
	if (!root)
		return;

	traverse_post_order(root->left, fn);
	traverse_post_order(root->right, fn);
	fn(*root);
}

using T = unsigned int;

class CP : public CP3
{
private:
	virtual void read_input() override
	{
		T x;
		while (read(x))
			pre_order_.push_back(x);
	}

	virtual void solve() override
	{
		const auto tree = make_from_pre_order(pre_order_.begin(), pre_order_.end());

		std::vector<T> post_order;
		post_order.reserve(pre_order_.size());

		traverse_post_order(
			tree, [&post_order](const Node<T>& node) { post_order.push_back(node.key); });

		write_vec(post_order, '\n');
		write_ln();
	}

private:
	std::vector<T> pre_order_;
};



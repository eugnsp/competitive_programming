/*********************************************************************
Array to BST
------------
URL: https://practice.geeksforgeeks.org/problems/array-to-bst/0

Given a sorted array. Write a program that creates a Balanced BST
using array elements. If there are N elements in array, then
floor(n/2)-th element should be chosen as root and same should be
followed recursively.

Input
-----
The first line of input contains an integer T, denoting the number of
test cases. The first line of each test case is N(size of array).
The second line of each test case contains N input A[].

Output
------
Print the preorder traversal of constructed BST.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <vector>
#include <memory>

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
Node_ptr<T> make(It first, It last)
{
	Node_ptr<T> root;
	if (first == last)
		return root;

	const auto mid = first + (last - first - 1) / 2;

	root.reset(new Node<T>{*mid});
	root->left = make(first, mid);
	root->right = make(mid + 1, last);

	return root;
}

template<typename T, class Fn>
void traverse_pre_order(const Node_ptr<T>& root, Fn&& fn)
{
	if (!root)
		return;

	fn(root);
	traverse_pre_order(root->left, fn);
	traverse_pre_order(root->right, fn);
}

using T = unsigned int;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(seq_);
	}

	virtual void solve(unsigned int) override
	{
		const auto tree = make(seq_.begin(), seq_.end());
		traverse_pre_order(tree, [](const Node_ptr<T>& node)
			{ write(node->key, ' '); });

		write_ln();
	}

private:
	std::vector<T> seq_;
};

MAIN(CP)

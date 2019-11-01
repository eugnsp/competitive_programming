/*********************************************************************
Tree recovery
-------------
UVa ID: 005 36

Little Valentine liked playing with binary trees very much. Her
favorite game was constructing randomly looking binary trees with
capital letters in the nodes. To record her trees for future
generations, she wrote down two strings for each tree: a preorder
traversal (root, left subtree, right subtree) and an inorder traversal
(left subtree, root, right subtree). She thought that such a pair of
strings would give enough information to reconstruct the tree later
(but she never tried it). Now, years later, looking again at the
strings, she realized that reconstructing the trees was indeed
possible, but only because she never had used the same letter twice
in the same tree. However, doing the reconstruction by hand, soon
turned out to be tedious. So now she asks you to write a program that
does the job for her!

Input
-----
The input file will contain one or more test cases. Each test case
consists of one line containing two strings "preord" and "inord",
representing the preorder traversal and inorder traversal of a binary
tree. Both strings consist of unique capital letters. (Thus they are
not longer than 26 characters.) Input is terminated by end of file.

Output
------
For each test case, recover Valentine's binary tree and print one line
containing the tree's postorder traversal (left subtree, right subtree,
root).

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <memory>
#include <string>
#include <string_view>

struct Node;
using Node_ptr = std::unique_ptr<Node>;

struct Node
{
	char data;
	Node_ptr left;
	Node_ptr right;
};

Node_ptr deserialize_pre_in(std::string_view pre, std::string_view in)
{
	assert(pre.length() == in.length());

	// <pre-order> = <root><pre-order of left tree><pre-order of right tree>
	// <in-order> = <in-order of left tree><root><in-order of right tree>

	if (pre.empty())
		return {};

	const auto left_length = in.find(pre[0]);
	assert(left_length != std::string::npos);

	auto t = std::make_unique<Node>();
	t->data = pre[0];
	t->left = deserialize_pre_in(pre.substr(1, left_length), in.substr(0, left_length));
	t->right = deserialize_pre_in(pre.substr(left_length + 1), in.substr(left_length + 1));

	return t;
}

std::string serialize_post(const Node_ptr& t)
{
	if (!t)
		return {};
	return serialize_post(t->left) + serialize_post(t->right) + t->data;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(pre_order_, in_order_);
	}

	virtual void solve(unsigned int) override
	{
		const auto tree = deserialize_pre_in(pre_order_, in_order_);
		write_ln(serialize_post(tree));
	}

private:
	std::string pre_order_;
	std::string in_order_;
};

MAIN

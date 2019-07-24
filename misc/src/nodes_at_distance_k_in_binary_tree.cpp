/*********************************************************************
Nodes at distance k in binary tree
----------------------------------

In the given binary tree with no parent pointers, for the given target
node T and the given integer value k, iterate over all the nodes that
are at distance k from the the node T.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "uptr_binary_tree.hpp"
#include <cstddef>
#include <optional>

template<class T, class Fn>
void iterate_nodes_at_distance(const Node_ptr<T>& root, std::size_t k, Fn&& fn)
{
	if (!root)
		return;

	if (k == 0)
		fn(*root);
	else
	{
		iterate_nodes_at_distance(root->left, k - 1, fn);
		iterate_nodes_at_distance(root->right, k - 1, fn);
	}
}

template<typename T, class Fn>
std::optional<std::size_t> iterate_nodes_at_distance(const Node_ptr<T>& root, const T& target, std::size_t k, Fn&& fn)
{
	if (!root)
		return {};
	if (root->data == target)
	{
		iterate_nodes_at_distance(root, k, fn);
		return 1;
	}

	if (const auto left = iterate_nodes_at_distance(root->left, target, k, fn); left)
		if (*left == k)
			fn(*root);
		else
		{
			iterate_nodes_at_distance(root->right, k - *left - 1, fn);
			return *left + 1;
		}
	else if (const auto right = iterate_nodes_at_distance(root->right, target, k, fn); right)
	{
		if (*right == k)
			fn(*root);
		else
		{
			iterate_nodes_at_distance(root->left, k - *right - 1, fn);
			return *right + 1;
		}
	}
	return {};
}

using T = int;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_tree(tree_);
		read(target_node_, distance_);
	}

	virtual void solve(unsigned int) override
	{
		iterate_nodes_at_distance(tree_, target_node_, distance_, [](const Node<T>& node) { write(node.data, ' '); });
		write_ln();
	}

private:
	Node_ptr<T> tree_;
	T target_node_;
	std::size_t distance_;
};

MAIN

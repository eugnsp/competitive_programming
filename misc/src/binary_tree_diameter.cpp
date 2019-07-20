/*********************************************************************
Binary tree diameter
--------------------

Find the diameter of the given binary tree. The diameter of a tree is
the number of nodes on the longest path between two leaves in the tree.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "uptr_binary_tree.hpp"
#include <algorithm>
#include <cstddef>
#include <initializer_list>

struct Info
{
	std::size_t diameter;
	std::size_t height;
};

template<typename T>
Info binary_tree_diameter_and_height(const Node_ptr<T>& root)
{
	if (!root)
		return {0, 0};

	const auto left = binary_tree_diameter_and_height(root->left);
	const auto right = binary_tree_diameter_and_height(root->right);

	const auto diameter = std::max({left.diameter, right.diameter, left.height + 1 + right.height});
	const auto height = std::max(left.height, right.height) + 1;
	return {diameter, height};
}

template<typename T>
std::size_t binary_tree_diameter(const Node_ptr<T>& root)
{
	return binary_tree_diameter_and_height(root).diameter;
}

using T = unsigned int;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_tree(tree_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(binary_tree_diameter(tree_));
	}

private:
	Node_ptr<T> tree_;
};

MAIN

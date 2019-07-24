/*********************************************************************
Check if a binary tree is a subtree
-----------------------------------

For the two given binary trees, check if the first tree is a subtree
of the second one.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "uptr_binary_tree.hpp"

template<typename T1, typename T2>
bool is_subtree(const Node_ptr<T1>& tree1, const Node_ptr<T2>& tree2)
{
	if (!tree1 && !tree2)
		return true;
	if (!tree1 || !tree2)
		return false;

	if (tree1->data == tree2->data)
		return is_subtree(tree1->left, tree2->left) && is_subtree(tree1->right, tree2->right);
	else
		return is_subtree(tree1->left, tree2) || is_subtree(tree1->right, tree2);
}

using T = int;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_tree(tree1_);
		read_tree(tree2_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(is_subtree(tree2_, tree1_) ? 1 : 0);
	}

private:
	Node_ptr<T> tree1_;
	Node_ptr<T> tree2_;
};

MAIN

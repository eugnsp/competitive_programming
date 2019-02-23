/*********************************************************************
Flip sort
---------
UVa ID: 103 27

Sorting in computer science is an important part. Almost every problem
can be solved effeciently if sorted data are found. There are some
excellent sorting algorithm which has already acheived the lower
bound n * lgn. In this problem we will also discuss about a new
sorting approach. In this approachonly one operation (flip) is
available and that is you can exchange two adjacent terms. If you
think awhile, you will see that it is always possible to sort a set of
numbers in this way. A set of integers will be given. Now using the
above approach we want to sort the numbers in ascending order.
You have to find out the minimum number of flips required.

Input
-----
The input will start with a positive integer N (N <= 1000). In next
few lines there will be N integers. Input will be terminated by EOF.

Output
------
For each data set print "Minimum exchange operations : M", where M is
the minimum flip operations required to perform sorting. Use a
seperate line for each case.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>
#include <memory>

template<typename T>
class AVL_tree
{
private:
	struct Node;
	using Ptr = std::unique_ptr<Node>;

	struct Node
	{
		T value;

		Ptr left;
		Ptr right;
		int height = 1;
		std::size_t n_descendants = 0;

		Node(T value) : value(value)
		{}
	};

public:
	std::size_t insert_and_count_inversions(const T& value)
	{
		return insert_and_count_inversions(value, root_);
	}

private:
	static int height(const Ptr& node_ptr)
	{
		return node_ptr ? node_ptr->height : 0;
	}

	static int height_diff(Node& node)
	{
		return height(node.left) - height(node.right);
	}

	static void update_height(Node& node)
	{
		node.height = std::max(height(node.left), height(node.right)) + 1;
	}

	static std::size_t n_descendants_plus_itself(const Ptr& node_ptr)
	{
		return node_ptr ? (node_ptr->n_descendants + 1) : 0;
	}

	static std::size_t insert_and_count_inversions(const T& value, Ptr& root)
	{
		if (!root)
		{
			root.reset(new Node{value});
			return 0;
		}
		else
		{
			++root->n_descendants;

			auto n_inversions = insert_and_count_inversions(value, value < root->value ? root->left : root->right);
			if (value < root->value)
				n_inversions += 1 + n_descendants_plus_itself(root->right);

			update_height(*root);
			rebalance(root);

			return n_inversions;
		}
	}

	static void rebalance(Ptr& root)
	{
		const auto diff = height_diff(*root);
		if (diff > 1)
		{
			if (height_diff(*root->left) >= 0)
				rotate_right(root);
			else
				rotate_left_right(root);
		}
		else if (diff < -1)
		{
			if (height_diff(*root->right) <= 0)
				rotate_left(root);
			else
				rotate_right_left(root);
		}
	}

	static void rotate(Ptr& root, Ptr Node::* side1, Ptr Node::* side2)
	{
		const auto node_x = root.release();
		const auto node_y = (node_x->*side1).release();
		const auto node_b = (node_y->*side2).release();

		(node_x->*side1).reset(node_b);
		(node_y->*side2).reset(node_x);
		root.reset(node_y);

		node_y->n_descendants += 1 + n_descendants_plus_itself(node_x->*side2);
		node_x->n_descendants -= 1 + n_descendants_plus_itself(node_y->*side1);
		update_height(*node_x);
	}

	static void rotate_right(Ptr& root)
	{
		rotate(root, &Node::left, &Node::right);
	}

	static void rotate_left(Ptr& root)
	{
		rotate(root, &Node::right, &Node::left);
	}

	static void rotate_left_right(Ptr& node)
	{
		rotate_left(node->left);
		rotate_right(node);
	}

	static void rotate_right_left(Ptr& node)
	{
		rotate_right(node->right);
		rotate_left(node);
	}

private:
	std::unique_ptr<Node> root_;
};

using T = int;

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_size_vec(numbers_);
	}

	virtual void solve(unsigned int) override
	{
		AVL_tree<T> tree;

		std::size_t n_inversions = 0;
		for (auto n : numbers_)
			n_inversions += tree.insert_and_count_inversions(n);

		write_ln("Minimum exchange operations : ", n_inversions);
	}

private:
	std::vector<T> numbers_;
};

MAIN(CP)

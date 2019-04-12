/*********************************************************************
Count smaller elements on the right
-----------------------------------

For the given array for each its element count the number of smaller
elements on the right.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <memory>
#include <vector>

using Element = int;

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
	std::size_t insert_and_count_lesser(const T& value)
	{
		return insert_and_count_lesser(value, root_);
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

	static std::size_t insert_and_count_lesser(const T& value, Ptr& root)
	{
		if (!root)
		{
			root.reset(new Node{value});
			return 0;
		}
		else
		{
			++root->n_descendants;

			auto n_lesser = insert_and_count_lesser(value, value <= root->value ? root->left : root->right);
			if (value > root->value)
				n_lesser += 1 + n_descendants_plus_itself(root->left);

			update_height(*root);
			rebalance(root);

			return n_lesser;
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

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(numbers_);
	}

	virtual void solve(unsigned int) override
	{
		AVL_tree<Element> tree;

		std::vector<std::size_t> n_lesser(numbers_.size());
		for (std::size_t i = numbers_.size(); i > 0; --i)
			 n_lesser[i - 1] = tree.insert_and_count_lesser(numbers_[i - 1]);

		write_vec(n_lesser, ' ');
		write_ln();
	}

private:
	std::vector<Element> numbers_;
};



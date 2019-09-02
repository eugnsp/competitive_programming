/*********************************************************************
Black box
---------
UVa ID: 005 01

Our Black Box represents a primitive database. It can save an integer
array and has a special i variable. At the initial moment Black Box is
empty and i = 0. This Black Box processes a sequence of transactions.
There are two types of transactions:
	ADD(x): put element x into Black Box;
	GET: increase i by 1 and give an i-th minimum out of all integers
		 containing in the Black Box.
Keep in mind that i-th minimum is a number located at i-th place after
Black Box elements sorting by non-descending.

Input
-----
The first line of the input is an integer K, then a blank line
followed by K datasets. There is a blank line between datasets. Input
for each dataset contains (in given order):
	M N A(1) A(2) ... A(M) u(1) u(2) ... u(N)
All numbers are divided by spaces and (or) carriage return characters.

Output
------
For each dataset, write to the output Black Box answers sequence for a
given sequence of transactions. Write only a number per line in the
output. Print a blank line between datasets.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <memory>
#include <numeric>
#include <vector>

template<typename T>
class AVL_tree
{
private:
	struct Node;
	using Ptr = std::unique_ptr<Node>;

	struct Node
	{
		T value;

		const Node* parent;
		Ptr left;
		Ptr right;
		int height = 1;

		Node(T value, const Node* parent) : value(value), parent(parent)
		{}

		bool is_left_child() const
		{
			return parent && this == parent->left.get();
		}

		bool is_right_child() const
		{
			return parent && this == parent->right.get();
		}
	};

public:
	class Iterator
	{
	public:
		explicit Iterator(const Node* ptr) : ptr_(ptr)
		{}

		const T& operator*() const
		{
			return ptr_->value;
		}

		void operator--()
		{
			if (ptr_->left)
			{
				goto_left(ptr_);
				while (ptr_->right)
					goto_right(ptr_);
			}
			else
			{
				while (ptr_->is_left_child())
					goto_parent(ptr_);
				goto_parent(ptr_);
			}
		}

		void operator++()
		{
			if (ptr_->right)
			{
				goto_right(ptr_);
				while (ptr_->left)
					goto_left(ptr_);
			}
			else
			{
				while (ptr_->is_right_child())
					goto_parent(ptr_);
				goto_parent(ptr_);
			}
		}

	private:
		static void goto_parent(const Node*& node)
		{
			node = node->parent;
		}

		static void goto_left(const Node*& node)
		{
			node = node->left.get();
		}

		static void goto_right(const Node*& node)
		{
			node = node->right.get();
		}

	private:
		const Node* ptr_;
	};

public:
	void insert(const T& value)
	{
		insert(value, root_);
	}

	Iterator root() const
	{
		return Iterator(root_.get());
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

	static void insert(const T& value, Ptr& root, Node* parent = nullptr)
	{
		if (!root)
			root.reset(new Node(value, parent));
		else
		{
			insert(value, (value < root->value) ? root->left : root->right, root.get());
			update_height(*root);
			rebalance(root);
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

	static void rotate(Ptr& root, Ptr Node::*side1, Ptr Node::*side2)
	{
		const auto node_x = root.release();
		const auto node_y = (node_x->*side1).release();
		const auto node_b = (node_y->*side2).release();
		if (node_b)
			node_b->parent = node_x;

		node_y->parent = node_x->parent;
		node_x->parent = node_y;

		(node_x->*side1).reset(node_b);
		(node_y->*side2).reset(node_x);

		root.reset(node_y);
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

using T = long;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t size_a, size_u;
		read(size_a, size_u);
		assert(size_a >= size_u);

		a_.clear();
		read_vec(size_a, a_);

		u_.clear();
		read_vec(size_u, u_);
	}

	virtual void solve(unsigned int i_case) override
	{
		if (i_case > 1)
			write_ln();

		AVL_tree<T> black_box;

		auto it = a_.begin();
		black_box.insert(*it++);
		auto box_it = black_box.root();

		std::adjacent_difference(u_.begin(), u_.end(), u_.begin());
		--u_.front();

		for (std::size_t j = 0; j < u_.size(); ++j)
		{
			for (std::size_t i = 0; i < u_[j]; ++i, ++it)
			{
				black_box.insert(*it);
				if (*it < *box_it)
					--box_it;
			}

			if (j > 0)
				++box_it;
			write_ln(*box_it);
		}
	}

private:
	std::vector<T> a_;
	std::vector<std::size_t> u_;
};

MAIN


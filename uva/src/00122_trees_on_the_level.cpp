/*********************************************************************
Trees on the level
------------------
UVa ID: 001 22

Given a sequence of binary trees, you are to write a program that
prints a level-order traversal of each tree. In this problem each node
of a binary tree contains a positive integer and all binary trees have
fewer than 256 nodes. In a level-order traversal of a tree, the data
in all nodes at a given level are printed in left-to-right order
and all nodes at level k are printed before all nodes at level k + 1.
In this problem a binary tree is specified by a sequence of pairs
(n,s) where n is the value at the node whose path from the root is
given by the strings. A path is given be a sequence of 'L's and 'R's,
where 'L' indicates a left branch and 'R' indicates a right branch.
binary tree is considered to be completely specified if every node
on all root-to-node paths in the tree is given a value exactly once.

Input
-----
The input is a sequence of binary trees specified as described above.
Each tree in a sequence consists of several pairs (n,s) as described
above separated by whitespace. The last entry in each tree is '()'.
No whitespace appears between left and right parentheses. All nodes
contain a positive integer. Every tree in the input will consist
of at least one node and no more than 256 nodes. Input is terminated
by end-of-file.

Output
------
For each completely specified binary tree in the input file, the
level order traversal of that tree should be printed. If a tree
is not completely specified, i.e., some node in the tree is NOT
given a value or a node is given a value more than once, then
the string 'not complete' should be printed.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <memory>
#include <optional>
#include <queue>
#include <string>
#include <vector>

template<typename T>
struct Node_descr
{
	T value;
	std::string path;
};

template<typename T>
class Binary_tree
{
public:
	static std::optional<Binary_tree> build(const std::vector<Node_descr<T>>& tree_descr)
	{
		Binary_tree tree;
		tree.root = std::make_unique<Node>();

		for (auto& node_descr : tree_descr)
		{
			auto node = &tree.root;
			for (const char ch : node_descr.path)
			{
				node = (ch == 'L') ? &(*node)->left : &(*node)->right;
				if (!*node)
					*node = std::make_unique<Node>();
			}

			if ((*node)->value)
				return {};
			(*node)->value = node_descr.value;
		}

		return std::move(tree);
	}

	std::vector<T> level_traversal() const
	{
		std::vector<T> values;
		std::queue<const Node*> nodes;

		nodes.push(root.get());
		while (!nodes.empty())
		{
			auto node = nodes.front();
			nodes.pop();

			if (node->value)
				values.push_back(*node->value);
			else
				return {};

			if (node->left)
				nodes.push(node->left.get());
			if (node->right)
				nodes.push(node->right.get());
		}

		return values;
	}

private:
	struct Node
	{
		std::optional<T> value;
		std::unique_ptr<Node> left;
		std::unique_ptr<Node> right;
	};

	std::unique_ptr<Node> root;
};

using Value = int;

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		tree_descr_.clear();

		std::string descr;
		while (read(descr))
		{
			const auto comma = descr.find(',');
			if (comma == std::string::npos)
				break;

			const auto value = std::stoi(descr.substr(1, comma - 1));
			const auto path = descr.substr(comma + 1, descr.length() - comma - 2);
			tree_descr_.push_back({value, path});
		}

		return !tree_descr_.empty();
	}

	virtual void solve(unsigned int) override
	{
		if (auto tree = Binary_tree<Value>::build(tree_descr_); tree)
		{
			if (auto level_traversal = tree->level_traversal(); level_traversal.empty())
				write_ln("not complete");
			else
			{
				write_range(level_traversal.begin(), level_traversal.end(), ' ');
				write_ln();
			}
		}
		else
			write_ln("not complete");
	}

private:
	std::vector<Node_descr<Value>> tree_descr_;
};

MAIN

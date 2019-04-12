/*********************************************************************
Tree summing
------------
UVa ID: 001 12

LISP was one of the earliest high-level programming languagesand,
with FORTRAN, is one of the oldest languages currently being used.
Lists, which are the fundamental data structures in LISP, can easily
be adapted to represent other important datastructures such as trees.
This problem deals with determining whether binary treesrepresented
as LISP S-expressions possess a certain property. Given a binary tree
of integers, you are to write a program that determines whether there
exists a root-to-leaf path whose nodes sum to a specified integer.
Binary trees are represented inthe input file as LISP S-expressions
having the following form:
	empty tree ::= ()
	tree ::= empty tree | (integer tree tree)
Note that with this formulation all leaves of a tree are of the form
(integer () ()). Since an empty tree has no root-to-leaf paths, any
query as to whether a path exists whose sum is a specified integer
in an empty tree must be answered negatively.

Input
-----
The input consists of a sequence of test cases in the form of
integer/tree pairs. Each test case consistsof an integer followed
by one or more spaces followed by a binary tree formatted as an
S-expressionas described above. All binary tree S-expressions will
be valid, but expressions may be spread overseveral lines and may
contain spaces. There will be one or more test cases in an input
file, and inputis terminated by end-of-file.

Output
------
There should be one line of output for each test case (integer/tree
pair) in the input file. For each pair I, T (I represents the integer,
T represents the tree) the output is the string "yes" if there is a
root-to-leaf path in T whose sum is I and "no" if there is no path
in T whose sum is I.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <memory>
#include <utility>
#include <vector>

using T = int;

struct Node
{
	Node(T val, std::unique_ptr<Node> l, std::unique_ptr<Node> r) :
		value(val), left(std::move(l)), right(std::move(r))
	{}

	bool is_leaf() const
	{
		return !left && !right;
	}

	T value;
	std::unique_ptr<Node> left;
	std::unique_ptr<Node> right;
};

std::unique_ptr<Node> read_tree()
{
	char ch;
	read(ch);
	assert(ch == '(');

	if (peek() == ')')
	{
		read(ch);
		return {};
	}

	T value;
	read(value);
	auto left = read_tree();
	auto right = read_tree();
	auto tree = std::unique_ptr<Node>(new Node(value, std::move(left), std::move(right)));

	read(ch);
	assert(ch == ')');

	return tree;
}

bool find_sum(T sum, const std::unique_ptr<Node>& root, T curr_sum = 0)
{
	if (!root)
		return false;

	curr_sum += root->value;
	return (curr_sum == sum && root->is_leaf()) || find_sum(sum, root->left, curr_sum) ||
		   find_sum(sum, root->right, curr_sum);
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		if (!read(sum_))
			return false;

		root_ = read_tree();
		return true;
	}

	virtual void solve(unsigned int) override
	{
		const auto b = find_sum(sum_, root_);
		write_ln(b ? "yes" : "no");
	}

private:
	T sum_;
	std::unique_ptr<Node> root_;
};



/*********************************************************************
Tree recovery
-------------
UVa ID: 005 36

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <memory>
#include <string>

struct Tree;
using Tree_ptr = std::unique_ptr<Tree>;

struct Tree
{
	char data;
	Tree_ptr left;
	Tree_ptr right;
};

Tree_ptr deserialize_by_pre_in(std::string pre, std::string in)
{
	assert(pre.length() == in.length());

	// <pre-order> = <root><pre-order of left tree><pre-order of right tree>
	// <in-order> = <in-order of left tree><root><in-order of right tree>

	if (pre.empty())
		return {};

	const auto left_length = in.find(pre[0]);
	assert(left_length != std::string::npos);

	auto t = std::unique_ptr<Tree>(new Tree);
	t->data = pre[0];
	t->left = deserialize_by_pre_in(pre.substr(1, left_length), in.substr(0, left_length));
	t->right = deserialize_by_pre_in(pre.substr(left_length + 1), in.substr(left_length + 1));

	return t;
}

std::string serialize_pre(const Tree_ptr& t)
{
	if (!t)
		return {};
	return t->data + serialize_pre(t->left) + serialize_pre(t->right);
}

std::string serialize_in(const Tree_ptr& t)
{
	if (!t)
		return {};
	return serialize_in(t->left) + t->data + serialize_in(t->right);
}

std::string serialize_post(const Tree_ptr& t)
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
		const auto tree = deserialize_by_pre_in(pre_order_, in_order_);

		assert(serialize_pre(tree) == pre_order_);
		assert(serialize_in(tree) == in_order_);

		write_ln(serialize_post(tree));
	}

private:
	std::string pre_order_;
	std::string in_order_;
};



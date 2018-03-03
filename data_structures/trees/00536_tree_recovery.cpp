/*********************************************************************
Tree recovery
-------------
UVa ID: 536

Goal:	find a post-order traversal of a tree,
		given its pre- and in-order traversals.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <memory>
#include <string>
#include <string_view>

struct Tree;
using Tree_ptr = std::unique_ptr<Tree>;

struct Tree
{
	char data;
	Tree_ptr left;
	Tree_ptr right;
};

Tree_ptr deserialize_by_pre_in(std::string_view pre, std::string_view in)
{
	assert(pre.length() == in.length());

	// <pre-order> = <root><pre-order of left tree><pre-order of right tree>
	// <in-order> = <in-order of left tree><root><in-order of right tree>

	if (pre.empty())
		return {};

	const auto left_length = in.find(pre[0]);
	assert(left_length != std::string_view::npos);

	auto t = std::make_unique<Tree>();
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
	virtual bool read_input(std::istream& in) override
	{
		in >> pre_order_ >> in_order_;
		return !!in;
	}

	virtual void solve(std::ostream& out, std::size_t) const override
	{
		const auto tree = deserialize_by_pre_in(pre_order_, in_order_);

		assert(serialize_pre(tree) == pre_order_);
		assert(serialize_in(tree) == in_order_);

		out << serialize_post(tree) << '\n';
	}

private:
	std::string pre_order_;
	std::string in_order_;
};

int main()
{
	CP p;
	return p.run();
}

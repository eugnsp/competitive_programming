/*********************************************************************
Tree recovery
-------------
UVa ID: 536

Goal:	find a post-order traversal of a tree,
		given its pre- and in-order traversals.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <string>
#include <string_view>
#include <algorithm>
#include <memory>
#include <cassert>

class Tree_recovery : public CP2
{
private:
	struct Tree;
	using Tree_ptr = std::unique_ptr<Tree>;

	struct Tree
	{
		char data;
		Tree_ptr left;
		Tree_ptr right;
	};

private:
	virtual bool read_input(std::istream& in) override
	{
		// <pre-order traversal> <in-order traversal>

		in >> pre_order_ >> in_order_;
		return !!in;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		const auto tree = deserialize_pre_order_and_in_order(pre_order_, in_order_);

		assert(serialize_pre_order(tree) == pre_order_);
		assert(serialize_in_order(tree) == in_order_);

		out << serialize_post_order(tree) << '\n';
	}

	static Tree_ptr deserialize_pre_order_and_in_order(std::string_view pre, std::string_view in)
	{
		assert(pre.length() == in.length());

		/*********************************************************************
		A binary tree can be deserialized recursively using the fact that for
		a tree with root <R>:
			<pre-order> = <R><pre-order of left tree><pre-order of right tree>
		and
			<in-order> = <in-order of left tree><R><in-order of right tree>.
		**********************************************************************/

		if (pre.empty())
			return {};

		const auto left_length = in.find(pre[0]);
		assert(left_length != std::string_view::npos);

		auto t = std::make_unique<Tree>();
		t->data = pre[0];
		t->left = deserialize_pre_order_and_in_order(pre.substr(1, left_length), in.substr(0, left_length));
		t->right = deserialize_pre_order_and_in_order(pre.substr(left_length + 1), in.substr(left_length + 1));
		
		return t;
	}

	static std::string serialize_pre_order(const Tree_ptr& t)
	{
		if (!t)
			return {};
		return t->data + serialize_pre_order(t->left) + serialize_pre_order(t->right);
	}

	static std::string serialize_in_order(const Tree_ptr& t)
	{
		if (!t)
			return {};
		return serialize_in_order(t->left) + t->data + serialize_in_order(t->right);
	}

	static std::string serialize_post_order(const Tree_ptr& t)
	{
		if (!t)
			return {};
		return serialize_post_order(t->left) + serialize_post_order(t->right) + t->data;
	}

private:
	std::string pre_order_;
	std::string in_order_;
};

int main()
{
	Tree_recovery p;
	return p.run();
}

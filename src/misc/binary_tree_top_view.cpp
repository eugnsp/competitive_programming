/*********************************************************************
Binary tree top view
--------------------

For the given binary tree find its top view.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "uptr_binary_tree.hpp"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <queue>
#include <utility>
#include <vector>

template<typename T, class Fn>
void tree_bfs(const Node_ptr<T>& root, Fn&& fn)
{
	std::queue<std::pair<Node<T>*, std::ptrdiff_t>> queue;
	queue.push({root.get(), 0});

	while (!queue.empty())
	{
		const auto node = queue.front().first;
		const auto hpos = queue.front().second;
		queue.pop();

		fn(*node, hpos);

		if (node->left)
			queue.push({node->left.get(), hpos - 1});
		if (node->right)
			queue.push({node->right.get(), hpos + 1});
	}
}

template<typename T, class Output_it>
void tree_top_view(const Node_ptr<T>& root, Output_it it)
{
	std::vector<const Node<T>*> left_view;
	std::vector<const Node<T>*> right_view;

	tree_bfs(root, [&left_view, &right_view](const auto& node, std::ptrdiff_t hpos)
	{
		if (hpos < 0)
		{
			if (left_view.size() < static_cast<std::size_t>(-hpos))
				left_view.push_back(&node);
		}
		else if (hpos > 0)
		{
			if (right_view.size() < static_cast<std::size_t>(hpos))
				right_view.push_back(&node);
		}
	});

	const auto deref_get_data = [](const Node<T>* node) { return node->data; };
	std::transform(left_view.rbegin(), left_view.rend(), it, deref_get_data);
	*it++ = root->data;
	std::transform(right_view.begin(), right_view.end(), it, deref_get_data);
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_tree(tree_);
	}

	virtual void solve(unsigned int) override
	{
		std::vector<int> top;
		tree_top_view(tree_, std::back_inserter(top));
		write_range(top.begin(), top.end(), ' ');
		write_ln();
	}

private:
	Node_ptr<int> tree_;
};

MAIN

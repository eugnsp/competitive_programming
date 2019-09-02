/*********************************************************************
Remove duplicate nodes
----------------------

Remove duplicated nodes from the given sorted singly-link list.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "uptr_list.hpp"
#include <cstddef>
#include <memory>
#include <utility>
#include <vector>

template<typename T, class Fn>
void traverse(const Node_ptr<T>& root, Fn&& fn)
{
	auto node = root.get();
	while (node)
	{
		fn(*node);
		node = node->next.get();
	}
}

template<class T>
void unique(Node_ptr<T>& root)
{
	for (auto node = &root; *node; node = &(*node)->next)
	{
		auto next_node = &(*node)->next;
		while (*next_node && (*node)->data == (*next_node)->data)
			next_node = &(*next_node)->next;
		(*node)->next = std::move(*next_node);
	}
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_list(list_);
	}

	virtual void solve(unsigned int) override
	{
		unique(list_);
		write_ln(list_);
	}

private:
	Node_ptr<int> list_;
};

MAIN

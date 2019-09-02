/*********************************************************************
Remove middle node
------------------

Remove the middle node from the given singly-link list (in the list
of n elements, the middle node is the ceil(n / 2)-th node).

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "uptr_list.hpp"
#include <utility>

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
void remove_mid(Node_ptr<T>& root)
{
	if (!root || !root->next)
	{
		root.reset();
		return;
	}

	auto slow = &root;
	auto fast = &root->next;

	while (true)
	{
		fast = &(*fast)->next;
		if (!*fast)
			break;
		fast = &(*fast)->next;
		if (!*fast)
			break;
		slow = &(*slow)->next;
	}

	(*slow)->next = std::move((*slow)->next->next);
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
		remove_mid(list_);
		write_ln(list_);
	}

private:
	Node_ptr<int> list_;
};

MAIN

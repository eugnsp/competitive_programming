/*********************************************************************
Remove middle node
------------------

Remove the middle node from the given singly-link list (in the list
of n elements, the middle node is the ceil(n / 2)-th node).

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <memory>
#include <utility>
#include <vector>

template<typename T>
struct Node;

template<typename T>
using Node_ptr = std::unique_ptr<Node<T>>;

template<typename T>
struct Node
{
	const T data;
	Node_ptr<T> next;

	explicit Node(T data) : data(std::move(data))
	{}
};

template<class It, typename T = typename std::iterator_traits<It>::value_type>
Node_ptr<T> make(It first, It last)
{
	Node_ptr<T> root;
	for (auto node = &root; first != last; ++first)
	{
		*node = std::make_unique<Node<T>>(*first);
		node = &(*node)->next;
	}

	return root;
}

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
		read_size_vec(seq_);
	}

	virtual void solve(unsigned int) override
	{
		auto list = make(seq_.begin(), seq_.end());
		remove_mid(list);
		traverse(list, [](const auto& node) { write(node.data, ' '); });

		write_ln();
	}

private:
	std::vector<int> seq_;
};

MAIN

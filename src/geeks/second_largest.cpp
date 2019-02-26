/*********************************************************************
Second largest
--------------

Given an array A of size N, print second largest element from an
array.

Input
-----
The first line of input contains an integer T denoting the number of
test cases. T test cases follow. Each test case contains two lines of
input. The first line contains an integer N denoting the size of the
array. The second line contains the N space seperated intgers of the
array.

Output
------
For each testcase, in a new line, print the second largest element.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <iterator>
#include <utility>
#include <vector>

template<class It>
bool cmp_dereference(It a, It b)
{
	return *a < *b;
}

template<class Node>
void combine(Node& node1, Node& node2)
{
	if (cmp_dereference(node1.first, node2.first))
	{
		node2.second.push_back(node1.first);
		node1 = std::move(node2);
	}
	else
		node1.second.push_back(node2.first);
}

// Returns the largest and the second largest elements in the range [first, last),
// for equivalent elements which one is returned is unspecified
template<class It>
std::pair<It, It> max_elements_1_2(It first, It last)
{
	assert(last - first > 1);

	// A node keeps an iterator to the element that have won and
	// a list of elements that competed with it (and have lost)
	using Node = std::pair<It, std::vector<It>>;
	std::vector<Node> binary_counter;

	const auto is_not_null = [&last](const Node& node) { return node.first != last; };
	const auto set_null = [&last](Node& node) { node.first = last; };

	// Populate the counter
	for (; first != last; ++first)
	{
		Node carry{first, {}};
		for (auto it = binary_counter.begin(); it != binary_counter.end(); ++it)
		{
			if (!is_not_null(*it))
			{
				*it = std::move(carry);
				set_null(carry);
				break;
			}

			combine(carry, *it);
			set_null(*it);
		}

		if (is_not_null(carry))
			binary_counter.push_back(carry);
	}

	// Reduce the counter
	auto it = std::find_if(binary_counter.begin(), binary_counter.end(), is_not_null);
	assert(it != binary_counter.end());

	auto max = *it;
	while (++it != binary_counter.end())
		if (is_not_null(*it))
			combine(max, *it);

	const auto max2 = std::max_element(max.second.begin(), max.second.end(),
		[](It a, It b) { return cmp_dereference(a, b); });
	assert(max2 != max.second.end());

	return {max.first, *max2};
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
		auto max = max_elements_1_2(seq_.begin(), seq_.end());
		write_ln(*max.second);
	}

private:
	std::vector<int> seq_;
};

MAIN(CP)

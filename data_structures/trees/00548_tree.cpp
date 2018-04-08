/*********************************************************************
Tree
----
UVa ID: 005 48

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <sstream>
#include <string>
#include <vector>

using T = unsigned int;
using Container = std::vector<T>;
using It = Container::const_iterator;

constexpr auto invalid_terminal = static_cast<T>(-1);
constexpr auto max_value = static_cast<T>(-1);

struct Path
{
	T terminal = invalid_terminal;
	T value = max_value;

	bool operator<(const Path& other) const
	{
		if (value != other.value)
			return value < other.value;
		else
			return terminal < other.terminal;
	}

	Path operator+(T val) const
	{
		auto path{*this};
		path.value += val;
		return path;
	}
};

Path deserialize_and_find_least_path(It in_begin, It in_end, It post_begin, It post_end)
{
	assert(in_begin <= in_end && post_begin <= post_end);

	// <in-order> = <in-order of left><root><in-order of right>
	// <post-order> = <post-order of left><post-order of right><root>

	if (post_begin == post_end)
		return {};

	const bool is_leaf = (post_end - post_begin == 1);
	if (is_leaf)
	{
		Path path;
		path.terminal = path.value = *post_begin;
		return path;
	}

	const auto value = *(post_end - 1);
	const auto root = std::find(in_begin, in_end, value);
	assert(root != in_end);

	const auto post_right = post_begin + (root - in_begin);
	const auto left = deserialize_and_find_least_path(in_begin, root, post_begin, post_right);
	const auto right = deserialize_and_find_least_path(root + 1, in_end, post_right, post_end - 1);

	return std::min(left, right) + value;
}

class CP : public CP2
{
private:
	virtual bool read_input(std::istream& in) override
	{
		std::string in_order_str, post_order_str;

		std::getline(in, in_order_str);
		std::getline(in, post_order_str);

		std::istringstream in_order(in_order_str), post_order(post_order_str);

		in_order_.clear();
		post_order_.clear();

		T value;
		while (in_order >> value)
		{
			assert(between(value, 1, 10000));
			in_order_.push_back(value);
		}

		while (post_order >> value)
		{
			assert(between(value, 1, 10000));
			post_order_.push_back(value);
		}

		assert(in_order_.size() == post_order_.size());
		assert(in_order_.size() <= 10000);

		return !!in;
	}

	virtual void solve(std::ostream& out, unsigned int) const override
	{
		const auto path = deserialize_and_find_least_path(
			in_order_.begin(), in_order_.end(), post_order_.begin(), post_order_.end());

		assert(path.terminal != invalid_terminal);
		out << path.terminal << '\n';
	}

private:
	Container in_order_;
	Container post_order_;
};

int main()
{
	CP p;
	return p.run();
}

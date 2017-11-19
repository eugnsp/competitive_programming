/*********************************************************************
Tree
----
UVa ID: 548

Goal:	find the value of the leaf node of a path of least value
		in a tree, given its pre- and in-order traversals.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cassert>

class Tree : public CP2
{
private:
	using T = unsigned int;
	using Container = std::vector<T>;
	using It = Container::const_iterator;

	static constexpr auto invalid_terminal = static_cast<T>(-1);
	static constexpr auto max_value = static_cast<T>(-1);

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

private:
	virtual bool read_input(std::istream& in) override
	{
		// <in-order traversal>
		// <post-order traversal>

		std::string in_order_str, post_order_str;

		std::getline(in, in_order_str);
		std::getline(in, post_order_str);

		std::istringstream in_order(in_order_str), post_order(post_order_str);

		in_order_.clear();
		post_order_.clear();

		T value;
		while (in_order >> value)
		{
			assert(0 < value && value < 10000);
			in_order_.push_back(value);
		}

		while (post_order >> value)
		{
			assert(0 < value && value < 10000);
			post_order_.push_back(value);
		}

		assert(in_order_.size() == post_order_.size());
		assert(in_order_.size() <= 10000);

		return !!in;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		const auto path = deserialize_and_find_least_path(
			in_order_.begin(), in_order_.end(), post_order_.begin(), post_order_.end());		
		
		assert(path.terminal != invalid_terminal);
		out << path.terminal << '\n';
	}

	static Path deserialize_and_find_least_path(It in_begin, It in_end, It post_begin, It post_end)
	{
		assert(in_begin <= in_end && post_begin <= post_end);

		/*********************************************************************
		A binary tree can be deserialized recursively using the fact that for
		a tree with root <R>:
			<in-order> = <in-order of left><R><in-order of right>
		and
			<post-order> = <post-order of left><post-order of right><R>.
		**********************************************************************/

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

private:
	Container in_order_;
	Container post_order_;
};

int main()
{
	Tree p;
	return p.run();
}

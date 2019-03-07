/*********************************************************************
Add all
-------
UVa ID: 109 54

The problem name reflects your task; just add a set of numbers. But
you may feel yourselves condescended, to write a C/C++ program just to
add a set of numbers. Such a problem will simply question your
erudition. So, lets add some flavor of ingenuity to it. Addition
operation requires cost now, and the cost is the summation of those
two to be added. So, to add 1 and 10, you need a cost of 11. If you
want to add 1, 2 and 3. There are several ways:
1 + 2 = 3, cost = 3		1 + 3 = 4, cost = 4		2 + 3 = 5, cost = 5
3 + 3 = 6, cost = 6		2 + 4 = 6, cost = 6		1 + 5 = 6, cost = 6
Total = 9				Total = 10				Total = 11
I hope you have understood already your mission, to add a set of
integers so that the cost is minimal.

Input
-----
Each test case will start with a positive number, N (2 <= N <= 5000)
followed by N positive integers (all are less than 100'000). Input is
terminated by a case where the value of N is zero. This case should
not be processed.

Output
------
For each case print the minimum total cost of addition in a single
line.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

// Min-heap class
template<typename T>
class Heap
{
public:
	// Build a min-heap from the elements in the range [first, last)
	template<class It>
	Heap(const It first, const It last) : heap_(first, last)
	{
		const auto first_internal = heap_.size() / 2;

		// Node i is a root of a min-heap
		for (auto i = first_internal + 1; i > 0; --i)
			sift_down(i - 1);
	}

	bool is_empty() const
	{
		return heap_.empty();
	}

	const T& top() const
	{
		return heap_.front();
	}

	void pop()
	{
		heap_.front() = std::move(heap_.back());
		heap_.pop_back();
		sift_down(0);
	}

	void push(T value)
	{
		heap_.push_back(std::move(value));
		sift_up();
	}

private:
	static std::size_t parent_index(const std::size_t child)
	{
		assert(child != 0);
		return (child - 1) / 2;
	}

	static std::size_t left_child_index(const std::size_t parent)
	{
		return 2 * parent + 1;
	}

	static std::size_t right_child_index(const std::size_t parent)
	{
		return 2 * parent + 2;
	}

	bool is_valid_node(std::size_t index) const
	{
		return index < heap_.size();
	}

	void sift_down(std::size_t index)
	{
		auto value = std::move(heap_[index]);

		while (true)
		{
			auto child = left_child_index(index);
			if (!is_valid_node(child))
				break;

			const auto right_child = right_child_index(index);
			if (is_valid_node(right_child) && heap_[right_child] < heap_[child])
				child = right_child;
			if (value <= heap_[child])
				break;

			heap_[index] = std::move(heap_[child]);
			index = child;
		}

		heap_[index] = std::move(value);
	}

	void sift_up()
	{
		auto value = std::move(heap_.back());
		auto child = heap_.size() - 1;
		while (child != 0)
		{
			const auto parent = parent_index(child);
			if (value >= heap_[parent])
				break;
			heap_[child] = std::move(heap_[parent]);
			child = parent;
		}
		heap_[child] = std::move(value);
	}

private:
	std::vector<T> heap_;
};

using T = unsigned int;

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_size_vec(numbers_);
	}

	virtual void solve(unsigned int) override
	{
		Heap<T> heap_(numbers_.begin(), numbers_.end());

		T cost = 0;
		while (true)
		{
			const auto n = heap_.top();
			heap_.pop();

			const auto nn = n + heap_.top();
			heap_.pop();

			cost += nn;
			if (heap_.is_empty())
				break;

			heap_.push(nn);
		}

		write_ln(cost);
	}

private:
	std::vector<T> numbers_;
};

MAIN(CP)

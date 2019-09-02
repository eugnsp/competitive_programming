/*********************************************************************
Nearly sorted
-------------

Sort the given array, in which each element is at most k positions
away from its position in the sorted array.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
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

	T& top()
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

	bool is_valid_node(const std::size_t index) const
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

template<class It>
std::size_t dist(const It first, const It last)
{
	return static_cast<std::size_t>(last - first);
}

template<class It>
void insertion_sort(const It first, const It last)
{
	if (first == last)
		return;

	// [first, it): sorted elements
	// [it, last):  not yet processed elements
	// At the beginning: it = first + 1
	// At the the end: it = last

	for (auto it = std::next(first); it != last; ++it)
	{
		auto value = std::move(*it);
		auto it2 = it;
		while (it2 != first && value < *std::prev(it2))
		{
			*it2 = std::move(*std::prev(it2));
			--it2;
		}
		*it2 = std::move(value);
	}
}

template<class It>
void heap_sort_k_sorted(It first, const It last, const std::size_t k)
{
	assert(k <= dist(first, last));

	using T = typename std::iterator_traits<It>::value_type;

	auto it = std::min(first + k + 1, last);
	Heap<T> heap(first, it);

	while (!heap.is_empty())
	{
		*first++ = heap.top();
		heap.pop();
		if (it != last)
			heap.push(*it++);
	}
}

template<class It>
void sort_k_sorted(const It first, const It last, const std::size_t k)
{
	write_ln(k);
	write_ln(dist(first, last));
	assert(k <= dist(first, last));

	constexpr std::size_t insertion_threshold = 32;
	if (std::min(dist(first, last), k) <= insertion_threshold)
		insertion_sort(first, last);
	else
		heap_sort_k_sorted(first, last, k);
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t size;
		read(size, k_);

		vec_.clear();
		read_vec(size, vec_);
	}

	virtual void solve(unsigned int) override
	{
		sort_k_sorted(vec_.begin(), vec_.end(), k_);
		write_range(vec_.begin(), vec_.end(), ' ');
		write_ln();
	}

private:
	std::size_t k_;
	std::vector<unsigned int> vec_;
};

MAIN

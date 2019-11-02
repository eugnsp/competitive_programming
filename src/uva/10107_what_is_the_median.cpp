/*********************************************************************
What is the median?
-------------------
UVa ID: 101 07

Median plays an important role in the world of statistics. By
definition, it is a value which divides an array into two equal parts.
In this problem you are to determine the current median of some long
integers. Suppose, we have five numbers {1, 3, 6, 2, 7}. In this case,
3 is the median as it has exactly two numbers on its each side, {1, 2}
and {6, 7}. If there are even number of values like {1, 3, 6, , 7, 8},
only one value cannot split this array into equal two parts, so we
consider the average of the middle values {3, 6}. Thus, the median
will be (3 + 6) / 2 = 4.5. In this problem, you have to print only
the integer part, not the fractional. As a result, according to this
problem, the median will be 4!

Input
-----
The input file consists of series of integers X (0 <= X < 2^31) and
total number of integers N is less than 10'000. The numbers may have
leading or trailing spaces.

Output
------
For each input print the current value of the median.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <functional>
#include <queue>
#include <utility>
#include <vector>

template<class T>
class Stream_median
{
public:
	T get() const
	{
		assert(!max_heap_.empty());

		if (max_heap_.size() > min_heap_.size())
			return max_heap_.top();
		else
			return (min_heap_.top() + max_heap_.top()) / 2;
	}

	void push(const T& value)
	{
		assert(min_heap_.size() == max_heap_.size() || min_heap_.size() + 1 == max_heap_.size());

		if (max_heap_.size() > min_heap_.size())
			rebalance_push(max_heap_, min_heap_, value < max_heap_.top(), value);
		else
			rebalance_push(
				min_heap_, max_heap_, !min_heap_.empty() && min_heap_.top() < value, value);

		assert(min_heap_.size() == max_heap_.size() || min_heap_.size() + 1 == max_heap_.size());
	}

private:
	template<class Heap1, class Heap2>
	static void rebalance_push(Heap1& heap1, Heap2& heap2, bool push_to_heap1, const T& value)
	{
		if (push_to_heap1)
		{
			heap2.push(std::move(heap1.top()));
			heap1.pop();
			heap1.push(value);
		}
		else
			heap2.push(value);
	}

private:
	std::priority_queue<T, std::vector<T>, std::greater<T>> min_heap_;
	std::priority_queue<T, std::vector<T>, std::less<T>> max_heap_;
};

class CP : public CP3
{
private:
	virtual void read_input() override
	{
		unsigned int value;
		while (read(value))
			values_.push_back(value);
	}

	virtual void solve() override
	{
		Stream_median<unsigned int> stream_median;
		for (const auto value : values_)
		{
			stream_median.push(value);
			write_ln(stream_median.get());
		}
	}

private:
	std::vector<unsigned int> values_;
};

MAIN

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
will be (3 + 6) / 2 = 4.5. In this problem, you have to print only the
integer part, not the fractional. As a result, according to this 
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
#include <vector>

using T = unsigned int;

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(value_);
	}

	virtual void solve(unsigned int) override
	{
		assert(min_heap_.size() == max_heap_.size()
			|| min_heap_.size() + 1 == max_heap_.size()
			|| min_heap_.size() == max_heap_.size() + 1);

		if (min_heap_.empty() && max_heap_.empty())
			max_heap_.push(value_);
		else
			if (value_ <= get_median())
				push_and_rebalance(max_heap_, min_heap_, value_);
			else
				push_and_rebalance(min_heap_, max_heap_, value_);

		write_ln(get_median());
	}

	T get_median() const
	{
		assert(!min_heap_.empty() || !max_heap_.empty());

		if (min_heap_.size() < max_heap_.size())
			return max_heap_.top();
		else if (min_heap_.size() > max_heap_.size())
			return min_heap_.top();
		else
			return (min_heap_.top() + max_heap_.top()) / 2;
	}

	template<class H1, class H2>
	static void push_and_rebalance(H1& heap1, H2& heap2, T value)
	{
		heap1.push(value);
		if (heap1.size() == heap2.size() + 2)
		{
			heap2.push(heap1.top());
			heap1.pop();
		}
	}

private:
	T value_;

	std::priority_queue<T, std::vector<T>, std::greater<T>> min_heap_;
	std::priority_queue<T, std::vector<T>, std::less<T>> max_heap_;
};

MAIN(CP)

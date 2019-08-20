/*********************************************************************
Min-stack
---------

Implement a stack that supports the min() operation in O(1) time.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cstddef>
#include <utility>
#include <vector>

template<typename T>
class Min_stack
{
public:
	void push(const T& value)
	{
		if (mins_.empty() || value <= min())
			mins_.push_back(stack_.size());
		stack_.push_back(value);
	}

	T pop()
	{
		T value = std::move(stack_.back());
		stack_.pop_back();
		if (value == min())
			mins_.pop_back();

		return value;
	}

	const T& min() const
	{
		return stack_[mins_.back()];
	}

	bool is_empty() const
	{
		return stack_.empty();
	}

private:
	std::vector<T> stack_;
	std::vector<std::size_t> mins_;
};

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(seq_);
	}

	virtual void solve(unsigned int) override
	{
		Min_stack<unsigned int> stack;
		for (auto value : seq_)
			stack.push(value);

		write_ln(stack.min());
	}

private:
	std::vector<unsigned int> seq_;
};

MAIN

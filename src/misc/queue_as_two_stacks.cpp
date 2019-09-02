/*********************************************************************
Queue as two stacks
-------------------

Implement queue using two stacks and process the given sequence of
commands:
	* E <value>	- enqueue value
	* D         - dequeue value

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <optional>
#include <stack>
#include <vector>

template<typename T>
class Queue
{
private:
	using St = std::stack<T>;

public:
	void push(const T& value)
	{
		move_stack(rev_stack_, stack_);
		rev_stack_.push(value);
		move_stack(stack_, rev_stack_);
	}

	const T& front() const
	{
		return rev_stack_.top();
	}

	void pop()
	{
		rev_stack_.pop();
	}

	bool is_empty() const
	{
		return rev_stack_.empty();
	}

private:
	static void move_stack(St& from, St& to)
	{
		while (!from.empty())
		{
			to.push(from.top());
			from.pop();
		}
	}

	St stack_;
	St rev_stack_;
};

template<class T>
struct Op
{
	char op;
	std::optional<T> value;
};

template<class T>
bool read(Op<T>& op)
{
	if (!read(op.op))
		return false;

	if (op.op == 'E')
	{
		T value;
		if (!read(value))
			return false;
		op.value = std::move(value);
	}
	return true;
}

using T = int;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(ops_);
	}

	virtual void solve(unsigned int) override
	{
		Queue<T> q;
		for (auto& op : ops_)
			switch (op.op)
			{
			case 'E':
				write_ln("Enqueue ", *op.value);
				q.push(*op.value);
				break;

			case 'D':
				write_ln("Dequeue ", q.front());
				q.pop();
				break;

			default:
				write_ln("Unknown operation");
			}

		write_ln(q.is_empty() ? "Queue is empty" : "Queue is not empty");
	}

private:
	std::vector<Op<T>> ops_;
};

MAIN

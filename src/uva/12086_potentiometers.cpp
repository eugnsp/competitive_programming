/*********************************************************************
Potentiometers
--------------
UVa ID: 120 86

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "bit.hpp"
#include <algorithm>
#include <cassert>
#include <vector>
#include <utility>

using Size = unsigned int;
using Resistance = unsigned int;

enum class Action_type
{
	SET,
	MEASURE
};

struct Action
{
	struct Set
	{
		Size index;
		Resistance value;
	};

	struct Measure
	{
		Size first;
		Size last;
	};

	Action_type type;
	union
	{
		Set set;
		Measure measure;
	};
};

template<typename Value, typename Size>
class Fenwick_tree
{
public:
	Fenwick_tree(std::vector<Value> init_values) : tree_(std::move(init_values))
	{
		for (Size index = 0; index < tree_.size(); ++index)
		{
			const auto parent = index | (index + 1);
			if (parent < tree_.size())
				tree_[parent] += tree_[index];
		}
	}

	// Returns the sum of elements in the closed range [first, last]
	Value sum(Size first, Size last) const
	{
		assert(first <= last && last < tree_.size());

		auto sum = tree_[last];
		last &= (last + 1);

		while (last > first)
		{
			sum += tree_[--last];
			last &= (last + 1);
		}

		while (first != last)
		{
			sum -= tree_[--first];
			first &= (first + 1);
		}

		return sum;
	}

	Value at(Size index) const
	{
		assert(index < tree_.size());
		return sum(index, index);
	}

	void add(Size index, Value value)
	{
		while (index < tree_.size())
		{
			tree_[index] += value;
			index |= (index + 1);
		}
	}

	void set(Size index, Value value)
	{
		add(index, value - at(index));
	}

private:
	std::vector<Value> tree_;
};

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		if (!read_size_vec(resistances_))
			return false;

		actions_.clear();
		char type;
		while (read(type) && type != 'E')
		{
			Action action;
			if (type == 'S')
			{
				action.type = Action_type::SET;
				read(action.set.index, action.set.value);
				--action.set.index; // To zero-based indexing
			}
			else
			{
				action.type = Action_type::MEASURE;
				read(action.measure.first, action.measure.last);
				--action.measure.first, --action.measure.last; // To zero-based indexing
			}
			actions_.push_back(action);
		}

		ignore_line();
		return true;
	}

	virtual void solve(unsigned int i_case) override
	{
		Fenwick_tree<Resistance, Size> tree(std::move(resistances_));

		if (i_case > 0)
			write_ln();

		write_ln("Case ", i_case + 1, ":");

		for (const auto& action : actions_)
			if (action.type == Action_type::SET)
				tree.set(action.set.index, action.set.value);
			else if (action.type == Action_type::MEASURE)
				write_ln(tree.sum(action.measure.first, action.measure.last));
	}

private:
	std::vector<Resistance> resistances_;
	std::vector<Action> actions_;
};



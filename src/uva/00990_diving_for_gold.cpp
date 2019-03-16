/*********************************************************************
Diving for gold
---------------
UVa ID: 009 90

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_zero_one_knapsack.hpp"
#include <cstddef>
#include <vector>
#include <cassert>

class CP : public CP2
{
private:
	struct Treasure
	{
		unsigned int amount;
		unsigned int depth;
	};

private:
	virtual bool read_input() override
	{
		if (!read(max_time_, speed_, n_treasures_))
			return false;

		treasures_.resize(n_treasures_);
		for (auto& t : treasures_)
		{
			read(t.depth, t.amount);
			assert(t.depth > 0 && t.amount > 0);
		}

		return true;
	}

	virtual void solve(unsigned int i_case) override
	{
		const auto weight = [this](std::size_t i) { return 3 * speed_ * treasures_[i].depth; };
		const auto value = [this](std::size_t i) { return treasures_[i].amount; };

		const auto ts = knapsack_max_value_and_items(n_treasures_, max_time_, weight, value);

		if (i_case > 0)
			write_ln();

		write_ln(ts.first);
		write_ln(ts.second.size());
		for (const auto i : ts.second)
			write_ln(treasures_[i].depth, ' ', treasures_[i].amount);
	}

private:
	std::size_t n_treasures_;
	unsigned int max_time_;
	unsigned int speed_;
	std::vector<Treasure> treasures_;
};



/*********************************************************************
Luggage
-------
UVa ID: 106 64

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_zero_one_knapsack.hpp"
#include <cstddef>
#include <vector>
#include <numeric>
#include <string>
#include <sstream>
#include <cassert>

class CP : public CP1
{
private:
	using Weight = unsigned int;

private:
	virtual void read_input() override
	{
		std::string line;
		read_ln(line);
		std::istringstream ss(line);

		Weight weight;
		weights_.clear();
		while (ss >> weight)
		{
			assert(weight > 0);
			weights_.push_back(weight);
		}
	}

	virtual void solve(unsigned int) override
	{
		const auto total_weight = std::accumulate(weights_.begin(), weights_.end(), static_cast<Weight>(0));
		if (total_weight % 2 == 1)
			write_ln("NO");
		else
		{
			const auto weight = [this](std::size_t i) { return weights_[i]; };
			const auto max_weight_in_one_boot = knapsack_max_value(weights_.size(), total_weight / 2, weight, weight);

			if (max_weight_in_one_boot == total_weight / 2)
				write_ln("YES");
			else
				write_ln("NO");
		}
	}

private:
	std::vector<Weight> weights_;
};

MAIN(CP)

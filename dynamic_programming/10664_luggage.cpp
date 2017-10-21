// Luggage
// -------
//
// Goal: determine if it is possible to distribute the suitcases
// into the boots so that the two boots weigh the same.
//
// UVa ID: 10664
// This file is covered by the LICENSE file in the root of this project.

#include "base.hpp"
#include "dp_zero_one_knapsack.hpp"
#include <cstddef>
#include <vector>
#include <numeric>
#include <string>
#include <sstream>
#include <iostream>
#include <cassert>

class Luggage : public Program1
{
private:
	using T = unsigned int;

private:
	virtual void read_input() override
	{
		// <weight_1> ... <weight_n>

		std::string line;
		std::getline(std::cin, line);
		std::istringstream ss(line);

		T weight;
		weights_.clear();
		while (ss >> weight)
		{
			assert(weight > 0);
			weights_.push_back(weight);
		}
	}

	virtual void solve(std::size_t) override
	{
		const auto total_weight = std::accumulate(weights_.begin(), weights_.end(), static_cast<T>(0));
		if (total_weight % 2 == 1)
			std::cout << "NO\n";
		else
		{
			const auto weight = [this](std::size_t i) { return weights_[i]; };
			const auto max_weight_in_one_boot = knapsack_max_value(weights_.size(), total_weight / 2, weight, weight);

			if (max_weight_in_one_boot == total_weight / 2)
				std::cout << "YES\n";
			else
				std::cout << "NO\n";
		}
	}

private:
	std::vector<T> weights_;
};

int main()
{
	Luggage p;
	return p.run();
}

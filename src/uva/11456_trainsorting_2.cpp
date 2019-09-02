/*********************************************************************
Trainsorting
------------
UVa ID: 114 56

Goal:	find the number of cars in the longest train that can be made.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <vector>

class CP : public CP1
{
private:
	using T = unsigned int;

private:
	virtual void read_input() override
	{
		read_size_vec(weights);
	}

	virtual void solve(unsigned int) override
	{
		const auto n_cars = weights.size();
		std::size_t max_length = 0;
		if (n_cars > 0)
		{
			weights.insert(weights.begin(), n_cars - 1, 0);
			std::reverse_copy(weights.begin() + n_cars, weights.end(), weights.begin());

			/*********************************************************************
			lis_end(length) is the smallest element (here, car weight) that ends
				the longest increasing subsequence of the (length).

			Algorithm (first step of patience sort):
				for each element (x) of the input sequence:
					if (x) > lis_end.back()
						append (x) to lis_end
					else
						replace element in lis_end that is greater or equal to (x).
			**********************************************************************/
			std::vector<T> lis_end;
			lis_end.push_back(weights.front());

			for (auto w : weights)
			{
				const auto pos = std::lower_bound(lis_end.begin(), lis_end.end(), w);
				if (pos == lis_end.end())
					lis_end.push_back(w);
				else
					*pos = w;
			}

			max_length = lis_end.size();
		}

		write_ln(max_length);
	}

private:
	std::vector<T> weights;
};

MAIN


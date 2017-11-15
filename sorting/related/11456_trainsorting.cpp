/*********************************************************************
Trainsorting
------------
UVa ID: 11456

Goal:	find the number of cars in the longest train that can be made.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cstddef>
#include <vector>
#include <algorithm>
#include <cassert>

class Trainsorting : public CP1
{
private:
	using T = unsigned int;

private:
	virtual void read_input(std::istream& in) override
	{
		// <number of cars = n>
		// <weight_1>
		// ...
		// <weight_n>

		in >> n_cars_;
		assert(n_cars_ <= 2000);

		weights.resize(n_cars_);
		for (auto& w : weights)
			in >> w;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{

		std::size_t max_length = 0;
		if (n_cars_ > 0)
		{
			weights.insert(weights.begin(), n_cars_ - 1, 0);
			std::reverse_copy(weights.begin() + n_cars_, weights.end(), weights.begin());

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

		out << max_length << '\n';
	}

private:
	std::size_t n_cars_;
	std::vector<T> weights;
};

int main()
{
	Trainsorting p;
	return p.run();
}

/*********************************************************************
Log jumping
-----------
UVa ID: 1372

Goal:	the maximum number of logs one can visit in the game.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cstddef>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

class Log_jumping : public CP1
{
private:
	virtual void read_input() override
	{
		// <number of logs> <length of a log>
		// <left x-coordinate of the log 1>
		// ...
		// <left x-coordinate of the log n>

		std::cin >> n_logs_ >> length_;
		
		assert(n_logs_ >= 1 && n_logs_ <= 5000);
		assert(length_ >= 1 && length_ <= 100000);

		x_coords_.resize(n_logs_);
		for (auto& x : x_coords_)
			std::cin >> x;
	}

	virtual void solve(std::size_t) override
	{
		// After sorting the maximum number of visited logs is
		// the size of the largest group in which every (i)-th log
		// overlaps with the (i-1)-th and (i-2)-th logs.

		std::sort(x_coords_.begin(), x_coords_.end());

 		std::size_t n_visit_max = 1;
 		std::size_t start = 0;
 
 		for (std::size_t i = 1; i < n_logs_; ++i)
 			if (i >= 2 && are_overlapped(i - 2, i))
 				n_visit_max = std::max(n_visit_max, i - start + 1);
 			else
 			{
 				start = i - 1;
 				if (n_visit_max < 2 && are_overlapped(start, i))
 					n_visit_max = 2;
 			}

		std::cout << n_visit_max << '\n';
	}

	bool are_overlapped(std::size_t i1, std::size_t i2) const
	{
		assert(i1 < i2);
		assert(x_coords_[i1] <= x_coords_[i2]);
		return x_coords_[i2] - x_coords_[i1] <= length_;
	}

private:
	std::size_t n_logs_;
	int length_;
	std::vector<int> x_coords_;
};

int main()
{
	Log_jumping p;
	return p.run();
}

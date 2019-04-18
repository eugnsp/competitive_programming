/*********************************************************************
Square
------
UVa ID: 103 64

Given a set of sticks of various lengths,is it possible to join
them end-to-end to form a square?

Input
-----
The first line of input contains N, thenumber of test cases. Each
test case begins with an integer 4 <= M <= 20, the number of sticks.
M integers follow; each gives the length of a stick - an integer
between 1 and 10'000.

Output
------
For each case, output a line containing "yes" if is is possible
to form a square; otherwise output "no".

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <bitset>
#include <cassert>
#include <cstddef>
#include <numeric>
#include <utility>
#include <vector>

template<typename T, std::size_t mask_length = 20>
class Decomposition_checker
{
public:
	Decomposition_checker(std::vector<T> values, std::size_t n_groups) :
		values_(std::move(values)), n_groups_(n_groups)
	{
		std::sort(values_.rbegin(), values_.rend());
	}

	bool operator()() const
	{
		const auto sum = std::accumulate(values_.begin(), values_.end(), static_cast<T>(0));
		if (sum % n_groups_ != 0)
			return false;

		group_sum_ = sum / n_groups_;
		if (values_.front() > group_sum_)
			return false;

		unused_mask_.reset();
		for (std::size_t i = 0; i < values_.size(); ++i)
			unused_mask_.set(i);

		return find_next();
	}

private:
	bool find_next(std::size_t next = 0, T sum = 0) const
	{
		if (sum == group_sum_)
		{
			sum = 0;
			next = 0;
		}

		for (auto index = next; index < values_.size(); ++index)
			if (unused_mask_.test(index))
			{
				const auto new_sum = sum + values_[index];
				if (new_sum > group_sum_)
					continue;
				if (new_sum == group_sum_ && unused_mask_.count() == 1)
					return true;

				unused_mask_.flip(index);
				if (find_next(index + 1, new_sum))
					return true;
				unused_mask_.flip(index);
			}

		return false;
	}

private:
	std::vector<T> values_;
	const std::size_t n_groups_;

	mutable T group_sum_;
	mutable std::bitset<mask_length> unused_mask_;
};

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(lengths_);
	}

	virtual void solve(unsigned int) override
	{
		constexpr auto n_sides = 4;
		Decomposition_checker<unsigned int> is_decomposable(lengths_, n_sides);
		write_ln(is_decomposable() ? "yes" : "no");
	}

private:
	std::vector<unsigned int> lengths_;
};



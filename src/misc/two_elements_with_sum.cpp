/*********************************************************************
Two elements with the given sum
-------------------------------

Determine if the given array has two elements with the given sum.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cstddef>
#include <unordered_set>
#include <vector>

template<class It, typename T>
bool has_two_elements_with_sum(It first, const It last, const T& sum)
{
	std::unordered_set<T> hash;
	for (; first != last; ++first)
	{
		if (hash.count(*first) > 0)
			return true;
		hash.insert(sum - *first);
	}

	return false;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t size;
		read(size, sum_);

		vec_.clear();
		read_vec(size, vec_);
	}

	virtual void solve(unsigned int) override
	{
		const auto f = has_two_elements_with_sum(vec_.begin(), vec_.end(), sum_);
		write_ln(f ? "Yes" : "No");
	}

private:
	std::vector<int> vec_;
	int sum_;
};

MAIN

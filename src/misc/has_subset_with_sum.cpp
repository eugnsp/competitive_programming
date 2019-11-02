/*********************************************************************
Has a subset with a sum
-----------------------

Check if the given set of numbers has a subset with the given sum.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <iterator>

template<class It, class T = typename std::iterator_traits<It>::value_type>
bool has_subset_with_sum(It first, const It last, const T& sum)
{
	if (sum == 0)
		return true;

	auto sum_neg = T{0};
	auto sum_pos = T{0};
	std::size_t count = 0;
	for (auto it = first; it != last; ++it, ++count)
	{
		if (*it < 0)
			sum_neg += *it;
		else if (*it > 0)
			sum_pos += *it;
	}

	if (sum < sum_neg || sum > sum_pos)
		return false;

	const auto n_vals = static_cast<std::size_t>(sum_pos - sum_neg + 1);
	Matrix<bool> q(count, n_vals);

	for (std::size_t j = 0; j < n_vals; ++j)
	{
		const auto s = static_cast<std::size_t>(*first - sum_neg);
    	q(0, j) = (j == s);
	}

	for (std::size_t i = 1; i < count; ++i)
	{
		++first;
    	for (std::size_t j = 0; j < n_vals; ++j)
		{
			const auto s = static_cast<std::size_t>(*first - sum_neg);
        	q(i, j) = (j == s || q(i - 1, j) || (s <= j && j < s + n_vals && q(i - 1, j - s)));
		}
	}

	return q(count - 1, sum);
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(seq_);
		read(sum_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(has_subset_with_sum(seq_.begin(), seq_.end(), sum_) ? 1 : 0);
	}

private:
	std::vector<int> seq_;
	int sum_;
};

MAIN

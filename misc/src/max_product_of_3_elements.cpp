/*********************************************************************
Maximum product of 3 elements
-----------------------------

For the given array of integers, find the maximum product of any three
elements of the array.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <initializer_list>
#include <limits>
#include <vector>
#include <type_traits>

template<typename S = void, class It,
	typename T = std::conditional_t<std::is_void_v<S>, typename std::iterator_traits<It>::value_type, S>>
T max_product_of_3(It first, const It last)
{
	T max3 = std::numeric_limits<T>::min();

	if (first == last)
		return max3;

	T min = *first;
	T max = *first;
	if (++first == last)
		return max3;

	T min2 = *first * min;
	T max2 = *first * max;
	min = std::min<T>(min, *first);
	max = std::max<T>(max, *first);
	if (++first == last)
		return max3;

	for (; first != last; ++first)
	{
		const T el = *first;
		max3 = std::max({max3, el * max2, el * min2});
		max2 = std::max({max2, el * max, el * min});
		min2 = std::min({min2, el * max, el * min});
		max = std::max(max, el);
		min = std::min(min, el);
	}

	return max3;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(seq_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(max_product_of_3<long long>(seq_.begin(), seq_.end()));
	}

private:
	std::vector<int> seq_;
};

MAIN

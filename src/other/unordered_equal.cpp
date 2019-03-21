/*********************************************************************
Unordered equal arrays
----------------------

For the two given arrays find whether they are equal or not. Two
arrays are defined to be equal if both of them contain same set of
elements, the order of elements may be different.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <iterator>
#include <unordered_map>
#include <utility>
#include <vector>

template<class It>
bool are_unordered_equal(It first1, const It last1, It first2, const It last2)
{
	if (last1 - first1 != last2 - first2)
		return false;

	using T = typename std::iterator_traits<It>::value_type;
	std::unordered_map<T, std::size_t> hash;
	hash.reserve(last1 - first1);

	while (first1 != last1)
		++hash[*first1++];

	while (first2 != last2)
	{
		auto& count = hash[*first2++];
		if (count > 0)
			--count;
		else
			return false;
	}

	// There can be no positive values in the hash table at this point
	// because the ranges [first1, last1) and [first2, last2) have equal sizes
	return true;
}

using T = unsigned long long;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t size;
		read(size);

		arr1_.clear();
		arr2_.clear();
		read_vec(size, arr1_);
		read_vec(size, arr2_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(are_unordered_equal(arr1_.begin(), arr1_.end(), arr2_.begin(), arr2_.end()));
	}

private:
	std::vector<T> arr1_;
	std::vector<T> arr2_;
};



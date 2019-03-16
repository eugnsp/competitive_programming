/*********************************************************************
Check if two arrays are equal or not
------------------------------------
URL: https://practice.geeksforgeeks.org/problems/check-if-two-arrays-are-equal-or-not/0

Given two arrays A and B of equal size N, the task is to find if given
arrays are equal or not. Two arrays are said to be equal if both of
them contain same set of elements, arrangements (or permutation) of
elements may be different though. If there are repetitions, then
counts of repeated elements must also be same for two array to be equal.

Input
-----
The first line of input contains an integer T denoting the no of test
cases. Then T test cases follow. Each test case contains 3 lines of
input. The first line contains an integer N denoting the size of the
array. The second line contains element of array A[]. The third line
contains elements of the array B[].

Output
------
For each test case, print 1 if the arrays are equal else print 0.

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
bool are_equal(It first1, It last1, It first2, It last2)
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
		write_ln(are_equal(arr1_.begin(), arr1_.end(), arr2_.begin(), arr2_.end()));
	}

private:
	std::vector<T> arr1_;
	std::vector<T> arr2_;
};



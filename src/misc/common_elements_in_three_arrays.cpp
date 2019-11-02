/*********************************************************************
Common elements in three array
------------------------------

Find common elements in the three given arrays.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <vector>

template<class It1, class It2, class It3>
std::vector<It1> common_elements(It1 first1, It1 last1, It2 first2,
								 It2 last2, It3 first3, It3 last3)
{
	std::vector<It1> common;

	while (first1 != last1 && first2 != last2 && first3 != last3)
		if (*first1 == *first2 && *first2 == *first3)
		{
			common.push_back(first1);
			++first1, ++first2, ++first3;
		}
		else if (*first1 < *first2)
			++first1;
		else if (*first2 < *first3)
			++first2;
		else
			++first3;

	return common;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t size1, size2, size3;
		read(size1, size2, size3);

		vec1_.clear();
		vec2_.clear();
		vec3_.clear();
		read_vec(size1, vec1_);
		read_vec(size2, vec2_);
		read_vec(size3, vec3_);
	}

	virtual void solve(unsigned int) override
	{
		const auto common = common_elements(
			vec1_.begin(), vec1_.end(), vec2_.begin(), vec2_.end(), vec3_.begin(), vec3_.end());
		write_range(
			common.begin(), common.end(), [](auto it) { return *it; }, ' ');
		write_ln();
	}

private:
	std::vector<unsigned long long> vec1_, vec2_, vec3_;
};

MAIN

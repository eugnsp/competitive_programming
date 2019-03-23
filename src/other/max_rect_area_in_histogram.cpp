/*********************************************************************
Maximum rectangular area in a histogram
---------------------------------------

For the given histogram find the maximum area of a rectangle that fits
inside it.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cstddef>
#include <stack>
#include <vector>

template<class It, typename T = typename std::iterator_traits<It>::value_type>
T max_histogram_area(const It first, const It last)
{
	std::stack<It> smallers;
	T max_area = 0;

	auto it = first;
	while (it != last || !smallers.empty())
	{
		while (!smallers.empty() && (it == last || *it < *smallers.top()))
		{
			const auto height = *smallers.top();
			smallers.pop();
			const auto width = smallers.empty() ? (it - first) : (it - smallers.top() - 1);
			max_area = std::max(max_area, static_cast<T>(height * width));
		}
		if (it != last)
			smallers.push(it++);
	}

	return max_area;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read_size_vec(histogram_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(max_histogram_area(histogram_.begin(), histogram_.end()));
	}

private:
	std::vector<unsigned long long> histogram_;
};

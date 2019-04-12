/*********************************************************************
Jill rides again
----------------
UVa ID: 005 07

Jill likes to ride her bicycle, but since the pretty city of Green
hills where she lives has grown, Jill often uses the excellent public
bus system for part of her journey. She has a folding bicycle which
she carries with her when she uses the bus for the first part of her
trip. When the bus reaches some pleasant part of the city, Jill gets
off and rides her bicycle. She follows the bus route until she reaches
her destination pr she comes to a part of the city she does not like.
In the latter event she will board the bus to finish her trip. Through
years of experience, Jill has rated each road on an integer scale of
"niceness". Positive niceness values indicate roads Jill likes;
negative values are used for roads she does not like. There are not
zero values. Jill plans where to leave the bus and start bicycling,
as well as where to stop bicycling and re-join the bus, so that the
sum of niceness values of the roads she bicycles on is maximized.
This means that she will some times cycle along a road she does not
like, provided that it joins up two other parts of her journey
involving roads she likes enough to compensate. It may be that no part
of the route is suitable for cycling so that Jill takes the bus for
its entire route. Conversely, it may be that the whole route is so
nice Jill will not use the bus at all. Since there are many different
bus routes, each with several stops at which Jill could leave or enter
the bus, she feels that a computer program could help her identify
the best part to cycle for each bus route.

Input
-----
The input file contains information on several bus routes. The first
line of the file is a single integer b representing the number of
route descriptions in the file. The identifier for each route (r) is
the sequence number within the data file, 1 <= r <= b. Each route
description begins with the number of stops on the route: an integers,
2 <= s <= 20'000 on a line by itself. The number of stops is followed
by s - 1 lines, each line i (1 <= i < s) is an integer ni representing
Jill's assessment of the niceness of the road betweenthe two stops i
and i + 1.

Output
------
For each router in the input file, your program should identify the
beginning bus stop i and the ending bus stop j that identify the
segment of the route which yields the maximal sum of niceness,
m = ni + n{i+1} + ... + n{j-1}. If more than one segment is maximally
nice, choose the one with the longest cycle ride (largest j - i).
To break ties in longest maximal segments, choose the segment that
begins with the earliest stop (lowest i). For each router in the input
file, print a line in the form:
	The nicest part of routeris between stops i and j
However, if the maximal sum is not positive, your program should print:
	Router has no nice parts

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <cstddef>
#include <iterator>
#include <utility>
#include <vector>

// Finds the contiguous subarray within the array ([first, last)) which has
// the largest sum, and returns the sum and the subarray closed range [n1, n2];
// for two or more such subarrays the longest one is returned,
// for two or more longest subarrays the first one is returned
template<class It, typename T = typename std::iterator_traits<It>::value_type>
std::pair<T, std::pair<It, It>> max_sum_and_range(It first, const It last)
{
	assert(first != last);

	auto sum = *first;
	auto max_sum = sum;

	auto range = std::make_pair(first, first);
	auto max_range = range;

	std::size_t length = 1;
	std::size_t max_length = length;

	for (++first; first != last; ++first)
	{
		if (sum >= 0)
		{
			sum += *first;
			++range.second;
			++length;
		}
		else
		{
			sum = *first;
			range = {first, first};
			length = 1;
		}

		if (sum > max_sum || (sum == max_sum && length > max_length))
		{
			max_sum = sum;
			max_range = range;
			max_length = length;
		}
	}

	return {max_sum, max_range};
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t n_stops;
		read(n_stops);
		assert(n_stops >= 2);

		nicenesses_.resize(n_stops - 1);
		for (auto& n : nicenesses_)
			read(n);
	}

	virtual void solve(unsigned int i_case) override
	{
		const auto max_sum = max_sum_and_range(nicenesses_.begin(), nicenesses_.end());

		if (max_sum.first > 0)
			write_ln("The nicest part of route ", i_case,
				" is between stops ", max_sum.second.first - nicenesses_.begin() + 1,
				" and ", max_sum.second.second - nicenesses_.begin() + 2);
		else
			write_ln("Route ", i_case, " has no nice parts");
	}

private:
	std::vector<int> nicenesses_;
};



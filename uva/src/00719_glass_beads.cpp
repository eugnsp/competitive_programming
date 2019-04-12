/*********************************************************************
Glass beads
-----------
UVa ID: 007 19

Once upon a time there was a famous actress. As you may expect, she
played mostly Antique Comedies most of all. All the people loved her.
But she was not interested in the crowds. Her big hobby were beads of
any kind. Many bead makers were working for her and they manufactured
new necklaces and bracelets every day. One day she called her main
Inspector of Bead Makers (IBM) and told him she wanted a very long and
special necklace. The necklace should be made of glass beads of
different sizes connected to each other but without any thread running
through the beads, so that means the beads can be disconnected at any
point. The actress chose the succession of beads she wants to have and
the IBM promised to make the necklace. But then he realized a problem.
The joint between two neighbouring beads is not very robust so it
is possible that the necklace will get torn by its own weight. The
situation becomes even worse when thenecklace is disjoined. Moreover,
the point of disconnection is very important. If there are small beads
at the beginning, the possibility of tearing is much higher than if
there were large beads. IBM wants to test the robustness of a necklace
so he needs a program that will be able to determine the worst possible
point of disjoining the beads. The description of the necklace is a
string A = a(1)a(2) ... a(m) specifying sizes of the particular beads,
where the last character a(m) is considered to precede character a(1)
in circular fashion. The disjoint point i is said to be worse than the
disjoint point j if and only if the string
a(i)a(i+1) ... a(n)a(1) ... a(i-1) is lexicografically smaller than
the string a(j)a(j+1) ... a(n)a(1) ... a(j-1). String a(1)a(2) ... a(n)
is lexicografically smaller than the string b(1)b(2) ... b(n) if and
only if there exists an integer i, i <= n, so that a(j) = b(j) for
each 1 <= j < i and a(i) < b(i).

Input
-----
The input consists of N cases. The first line of the input contains
only positive integer N. Then followthe cases. Each case consists
of exactly one line containing necklace description. Maximal length
of each description is 10'000 characters. Each bead is represented
by a lower-case character of the english alphabet (a-z), where
a < b < ... < z.

Output
------
For each case, print exactly one line containing only one integer -
number of the bead which is the first at the worst possible disjoining,
i.e. such i, that the string A[i] is lexicographically smallest among
all the n possible disjoinings of a necklace. If there are more than
one solution, print the one with the lowest i.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <string>

template<class It>
It cyclic_advance(It it, It first, It last, std::size_t step)
{
	const auto max_step = static_cast<size_t>(last - it);
	return (step < max_step) ? it + step : first + (step - max_step);
}

// Returns the beginning of the lexicographical minimal rotation
// of the range [first, last) using the Duval's algorithm
template<class It>
It min_cyclic_rotation(It first, It last)
{
	assert(first != last);

	auto min_first = first;				// beginning of the min. rotation
	auto it_first = min_first + 1;		// beginning of the min. rotation candidate
	std::size_t offset = 0;

	const auto n = static_cast<size_t>(last - first);
	while (true)
	{
		assert(min_first < it_first);

		const auto min = cyclic_advance(min_first, first, last, offset);
		const auto it = cyclic_advance(it_first, first, last, offset);

		if (*min == *it)
		{
			if (++offset == n)
				break;
			continue;
		}

		if (*min > *it)
		{
			std::swap(min_first, it_first);

			assert(it_first < last - offset);
			it_first += offset + 1;
			it_first = std::max(it_first, min_first + 1);
		}
		else
		{
			if (it_first >= last - offset - 1)
				break;
			it_first += offset + 1;
		}

		offset = 0;
	}

	return min_first;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(str_);
	}

	virtual void solve(unsigned int) override
	{
		const auto start = min_cyclic_rotation(str_.begin(), str_.end());
		write_ln(start - str_.begin() + 1);
	}

private:
	std::string str_;
};



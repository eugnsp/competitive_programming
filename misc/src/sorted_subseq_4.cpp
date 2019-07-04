/*********************************************************************
Sorted subsequence of size 4
----------------------------

For the given array A, find any 4 elements in it such that
A[i] < A[j] < A[k] < A[l] for i < j < k < l.


This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <array>
#include <cstddef>
#include <iterator>
#include <limits>
#include <optional>
#include <utility>
#include <vector>

using Element = int;

template<class It, typename T = typename std::iterator_traits<It>::value_type>
std::optional<std::array<T, 4>> find_seq4(It first, It last)
{
	T v0 = std::numeric_limits<T>::max();
	T v1 = std::numeric_limits<T>::max();
	T v2 = std::numeric_limits<T>::max();
	T v00, v000, v11;

	for (; first != last; ++first)
		if (*first <= v0)
			v0 = *first;
		else if (*first <= v1)
		{
			v1 = *first;
			v00 = v0;
		}
		else if (*first <= v2)
		{
			v2 = *first;
			v11 = v1;
			v000 = v00;
		}
		else
			return std::array<T, 4>{v000, v11, v2, *first};

	return {};
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
		const auto seq = find_seq4(seq_.begin(), seq_.end());
		if (seq)
			write_range(seq->begin(), seq->end(), ' ');
		else
			write("No sequence");
		write_ln();
	}

private:
	std::vector<Element> seq_;
};

MAIN

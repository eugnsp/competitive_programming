/*********************************************************************
Sorted subsequence of size 3
----------------------------

For the given array A, find any 3 elements in it such that
A[i] < A[j] < A[k] for i < j < k.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <array>
#include <cstddef>
#include <optional>
#include <utility>
#include <vector>
#include <iterator>

using Element = int;

template<class It, typename T = typename std::iterator_traits<It>::value_type>
std::optional<std::array<T, 3>> find_seq3(const It first, const It last)
{
	const auto size = static_cast<std::size_t>(last - first);
	if (size < 3)
		return {};

	constexpr auto invalid_index = static_cast<std::size_t>(-1);

	std::vector<std::size_t> lesser(size, invalid_index);
	std::vector<std::size_t> greater(size, invalid_index);

	std::size_t min_index = 0;
	for (std::size_t i = 1; i < size; ++i)
		if (first[i] > first[min_index])
			lesser[i] = min_index;
		else
			min_index = i;

	auto max_index = size - 1;
	for (auto i = size - 1; i > 0; --i)
		if (first[i - 1] < first[max_index])
			greater[i - 1] = max_index;
		else
			max_index = i - 1;

	for (std::size_t i = 1; i < size - 1; ++i)
		if (lesser[i] != invalid_index && greater[i] != invalid_index)
			return std::array<T, 3>{first[lesser[i]], first[i], first[greater[i]]};

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
		const auto seq = find_seq3(seq_.begin(), seq_.end());
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

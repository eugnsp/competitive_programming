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
#include <utility>
#include <vector>

using Element = int;

template<typename T>
std::pair<bool, std::array<T, 3>> find_seq3(const std::vector<T>& seq)
{
	constexpr auto invalid_index = static_cast<std::size_t>(-1);

	std::vector<std::size_t> lesser(seq.size(), invalid_index);
	std::vector<std::size_t> greater(seq.size(), invalid_index);

	std::size_t min_index = 0;
	for (std::size_t i = 1; i < seq.size(); ++i)
		if (seq[i] > seq[min_index])
			lesser[i] = min_index;
		else
			min_index = i;

	auto max_index = seq.size() - 1;
	for (auto i = seq.size() - 1; i > 0; --i)
		if (seq[i - 1] < seq[max_index])
			greater[i - 1] = max_index;
		else
			max_index = i - 1;

	for (std::size_t i = 1; i < seq.size() - 1; ++i)
		if (lesser[i] != invalid_index && greater[i] != invalid_index)
			return {true, {seq[lesser[i]], seq[i], seq[greater[i]]}};

	return {false, {}};
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
		const auto seq = find_seq3(seq_);
		if (seq.first)
			write_vec(seq.second, ' ');
		else
			write("No sequence");
		write_ln();
	}

private:
	std::vector<Element> seq_;
};

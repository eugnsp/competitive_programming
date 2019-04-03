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
#include <limits>
#include <optional>
#include <utility>
#include <vector>

using Element = int;

template<typename T>
std::optional<std::array<T, 4>> find_seq4(const std::vector<T>& seq)
{
	T v0 = std::numeric_limits<T>::max();
	T v1 = std::numeric_limits<T>::max();
	T v2 = std::numeric_limits<T>::max();
	T v00, v000, v11;

	for (std::size_t i = 0; i < seq.size(); ++i)
		if (seq[i] <= v0)
			v0 = seq[i];
		else if (seq[i] <= v1)
		{
			v1 = seq[i];
			v00 = v0;
		}
		else if (seq[i] <= v2)
		{
			v2 = seq[i];
			v11 = v1;
			v000 = v00;
		}
		else
			return std::array<T, 4>{v000, v11, v2, seq[i]};

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
		const auto seq = find_seq4(seq_);
		if (seq)
			write_range(seq->begin(), seq->end(), ' ');
		else
			write("No sequence");
		write_ln();
	}

private:
	std::vector<Element> seq_;
};

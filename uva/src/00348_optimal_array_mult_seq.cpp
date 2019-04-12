/*********************************************************************
Optimal array multiplication sequence
-------------------------------------
UVa ID: 003 48

Given the size of each array in a sequence of arrays to be multiplied,
you are to determine an optimal computational sequence. Optimality,
for this problem, is relative to the number of individual
multiplications required.

Input
-----
For each array in the multiple sequences of arrays to be multiplied
you will be given only the dimensions of the array. Each sequence will
consist of an integer N which indicates the number of arrays to be
multiplied, and then N pairs of integers, each pair giving the number
of rows and columns in an array; the order in which the dimensions are
given is the same as the order in which the arrays are to be multiplied.
A value of zero for N indicates the end of the input. N will be no
larger than 10.

Output
------
Assume the arrays are named A1, A2, ..., AN. Your output for each input
case is to be a line containing a parenthesized expression clearly
indicating the order in which the arrays are to be multiplied. Prefix
the output for each case with the case number (they are sequentially
numbered, starting with 1). Your output should strongly resemble that
shown in the samples shown below. If, by chance, there are multiple
correct sequences, any of these will be accepted as a valid answer.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cassert>
#include <cstddef>
#include <string>
#include <vector>

struct Split_cost
{
	std::size_t cost = static_cast<std::size_t>(-1);
	std::size_t split_index;
};

using Dp_matrix = Matrix<Split_cost>;

std::string parenthesization(const Dp_matrix& m, const std::size_t i, const std::size_t j)
{
	if (i == j)
		return 'A' + std::to_string(i + 1);

	const auto k = m(i, j).split_index;
	return '(' + parenthesization(m, i, k) + " x " + parenthesization(m, k + 1, j) + ')';
}

std::string parenthesization(const std::vector<std::size_t>& extents)
{
	const auto n_matrices = extents.size() - 1;
	assert(n_matrices >= 1);

	// m(i, j).cost is the minimum number of operations needed to compute the product(A_i ... A_j),
	// m(i, j).split_index is the index(k) at which the product (A_i ... A_k) (A_{k + 1} ... A_j)
	// is split in the optimal parenthesization
	Dp_matrix m(n_matrices, n_matrices);

	// Base case
	for (std::size_t i = 0; i < n_matrices; ++i)
		m(i, i).cost = 0;

	// Recurrences
	for (std::size_t d = 1; d < n_matrices; ++d)
		for (std::size_t i = 0; i < n_matrices - d; ++i)
		{
			const auto j = i + d;
			for (auto k = i; k < j; ++k)
			{
				// Cost of computing the outermost multiplication
				// in the expression (A_i ... A_k) (A_{k + 1} ... A_j)
				const auto product_cost = extents[i] * extents[k + 1] * extents[j + 1];

				const auto cost = m(i, k).cost + m(k + 1, j).cost + product_cost;
				if (cost < m(i, j).cost)
					m(i, j) = {cost, k};
			}
		}

	return parenthesization(m, 0, n_matrices - 1);
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::size_t n_matrices_;
		if (!read(n_matrices_) || n_matrices_ == 0)
			return false;

		extents_.resize(n_matrices_ + 1);
		for (std::size_t i = 0; i < n_matrices_; ++i)
		{
			std::size_t rows, cols;
			read(rows, cols);
			assert(rows > 0 && cols > 0);

			extents_[i] = rows;
			extents_[i + 1] = cols;
		}

		return true;
	}

	virtual void solve(unsigned int i_case) override
	{
		write_ln("Case ", i_case, ": ", parenthesization(extents_));
	}

private:
	std::vector<std::size_t> extents_;
};



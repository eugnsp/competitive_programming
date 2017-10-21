// Optimal Array Multiplication Sequence
// -------------------------------------
// (AKA parenthesization, AKA matrix-chain multiplication
//
// Goal: compute the optimal evaluation of a matrix product) and
// the string representation of the corresponding parenthesization.
//
// UVa ID: 348
// This file is covered by the LICENSE file in the root of this project.

#include "base.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <string>
#include <vector>
#include <iostream>
#include <cassert>

class Optimal_mult_seq : public Program2
{
private:
	virtual bool read_input() override
	{
		// <number of matrices>
		// <rows_1> <cols_1>
		// ...
		// <rows_n> <cols_n>

		std::size_t n;
		std::cin >> n;

		if (n == 0)
			return false;

		assert(n <= 10);

		extents_.resize(n + 1);
		for (std::size_t i = 0; i < n; ++i)
		{
			std::size_t rows, cols;
			std::cin >> rows >> cols;
			assert(rows > 0 && cols > 0);

			extents_[i] = rows;
			extents_[i + 1] = cols;
		}

		return true;
	}

	virtual void solve(std::size_t i_case) override
	{
		const auto n = extents_.size() - 1;
		m_.resize_and_fill(n, n, { });

		// m(i, j).cost is the minimum number of operations needed
		// to compute the product (A_i ... A_j),
		// m(i, j).split_index is the index(k) at which the product
		// (A_i ... A_k) (A_{k+1} ... A_j) is split in the optimal parenthesization.

		// The recurrence relation is:
		// m(i, j).cost = min {i <= k < j} [cost_ikj + m(i, k).cost + m(k + 1, j).cost],
		// m(i, j).split_index = corresponding k in the minimum,
		// where cost_ikj is the cost of computing the outermost multiplication
		// in the expression (A_i ... A_k) (A_{k+1} ... A_j).
		//
		// Base case: m(i, i).cost = 0 for all (i).

		for (std::size_t i = 0; i < n; ++i)
			m_(i, i).cost = 0;

		for (std::size_t d = 1; d < n; ++d)
			for (std::size_t i = 0; i < n - d; ++i)
			{
				const auto j = i + d;
				for (std::size_t k = i; k < j; ++k)
				{
					const auto product_cost = extents_[i] * extents_[k + 1] * extents_[j + 1];
					const auto cost = m_(i, k).cost + m_(k + 1, j).cost + product_cost;
					if (cost < m_(i, j).cost)
						m_(i, j) = {cost, k};
				}
			}

		std::cout << "Case " << i_case + 1 << ": " << parenthesization_string(0, n - 1) << '\n';
	}

	std::string parenthesization_string(std::size_t i, std::size_t j)
	{
		if (i == j)
			return "A" + std::to_string(i + 1);
		else
		{
			const auto k = m_(i, j).split_index;
			return '(' + parenthesization_string(i, k) + " x "
				+ parenthesization_string(k + 1, j) + ')';
		}
	}

private:
	struct Parenth
	{
		std::size_t cost = static_cast<std::size_t>(-1);
		std::size_t split_index = static_cast<std::size_t>(-1);
	};

	std::vector<std::size_t> extents_;
	Matrix<Parenth> m_;
};

int main()
{
	Optimal_mult_seq p;
	return p.run();
}

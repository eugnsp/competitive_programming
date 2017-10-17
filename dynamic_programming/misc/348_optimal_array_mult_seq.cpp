// Optimal Array Multiplication Sequence
// -------------------------------------
// (AKA parenthesization, AKA matrix-chain multiplication
//
// Goal: compute the optimal evaluation of a matrix product) and
// the string representation of the corresponding parenthesization.
//
// UVa ID: 348
// This file is covered by the LICENSE file in the root of this project.

#include "../../matrix.hpp"
#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

struct Min_cost_parenth
{
	std::size_t cost;
	std::size_t split_index;
};

std::string parenthesization_string(std::size_t i, std::size_t j,
	const Matrix<Min_cost_parenth>& m)
{
	if (i == j)
		return "A" + std::to_string(i + 1);
	else
	{
		const auto k = m(i, j).split_index;
		return '(' + parenthesization_string(i, k, m) + " x " +
			parenthesization_string(k + 1, j, m) + ')';
	}
}

// Returns the string representation of the optimal evaluation of a matrix product expression
// (each A_i is a (extents[i] x extents[i + 1])-matrix)
std::string parenthesization(const std::vector<std::size_t>& extents)
{
	assert(extents.size() >= 2);
	assert(std::all_of(extents.begin(), extents.end(), [](std::size_t d) { return d > 0; }));

	const auto n = extents.size() - 1;
	const auto max_size = static_cast<std::size_t>(-1);

	// m(i, j).cost =			the minimum number of operations needed
	//							to compute the product (A_i ... A_j),
	// m(i, j).split_index	= 	the index (k) at which the product
	//							(A_i ... A_k) (A_{k+1} ... A_j)
	//							is split in the optimal parenthesization
	Matrix<Min_cost_parenth> m(n, n, {max_size, 0});

	for (std::size_t i = 0; i < n; ++i)
		m(i, i).cost = 0;					// No multiplication has zero cost

	for (std::size_t l = 1; l < n; ++l)
		for (std::size_t i = 0; i < n - l; ++i)
		{
			const auto j = l + i;
			for (std::size_t k = i; k < j; ++k)
			{
				// The cost of computing the outermost multiplication in
				// the expression (A_i ... A_k) (A_{k+1} ... A_j)
				const auto product_cost = extents[i] * extents[k + 1] * extents[j + 1];

				const auto cost = m(i, k).cost + m(k + 1, j).cost + product_cost;
				if (cost < m(i, j).cost)
				{
					m(i, j).cost = cost;
					m(i, j).split_index = k;
				}
			}
		}

	return parenthesization_string(0, n - 1, m);
}

// <number of matrices>
// <rows_1> <cols_1>
// ...
// <rows_n> <cols_n>

int main()
{
	for (std::size_t i = 1; ; ++i)
	{
		std::size_t n;
		std::cin >> n;

		if (n == 0)
			break;

		std::vector<std::size_t> extents(n + 1);
		for (std::size_t i = 0; i < n; ++i)
		{
			std::size_t rows, cols;
			std::cin >> rows >> cols;
			extents[i] = rows;
			extents[i + 1] = cols;
		}

		std::cout << "Case " << i << ": " << parenthesization(extents) << '\n';
	}

	return 0;
}
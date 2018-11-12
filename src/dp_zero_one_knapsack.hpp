// Dynamic programming 0-1 knapsack common routines
// ------------------------------------------------
//
// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include "matrix.hpp"
#include <cstddef>
#include <utility>
#include <vector>
#include <algorithm>
#include <functional>
#include <cassert>

template<class Weight, class Value>
void knapsack(Matrix<std::result_of_t<Value(std::size_t)>>& m, Weight weight_func, Value value_func)
{
	assert(m.rows() >= 1 && m.cols() >= 1);

	const auto max_weight = m.rows() - 1;
	const auto n = m.cols() - 1;

	for (std::size_t i = 0; i <= max_weight; ++i)
		m(i, 0) = 0;

	for (std::size_t j = 0; j <= n; ++j)
		m(0, j) = 0;

	for (std::size_t j = 1; j <= n; ++j)
	{
		const auto weight = weight_func(j - 1);
		const auto value = value_func(j - 1);

		for (std::size_t i = 1; i <= max_weight; ++i)
		{
			m(i, j) = m(i, j - 1);
			if (weight <= i)
				m(i, j) = std::max(m(i, j), m(i - weight, j - 1) + value);
		}
	}
}

template<class Weight, class Value>
std::result_of_t<Value(std::size_t)> knapsack_max_value(
	std::size_t n, std::result_of_t<Weight(std::size_t)> max_weight,
	Weight weight_func,	Value value_func)
{
	Matrix<std::result_of_t<Value(std::size_t)>> m(max_weight + 1, n + 1);

	knapsack(m, weight_func, value_func);
	return m(max_weight, n);
}

template<class Weight, class Value>
std::pair<std::result_of_t<Value(std::size_t)>, std::vector<std::size_t>>
	knapsack_max_value_and_items(
		std::size_t n, std::result_of_t<Weight(std::size_t)> max_weight,
		Weight weight_func, Value value_func)
{
	Matrix<std::result_of_t<Value(std::size_t)>> m(max_weight + 1, n + 1);

	knapsack(m, weight_func, value_func);

	std::vector<std::size_t> items;
	auto i = max_weight;
	for (auto j = n; j > 0; --j)
		if (m(i, j) > m(i, j - 1))
		{
			items.push_back(j - 1);
			i -= weight_func(j - 1);
		}

	std::reverse(items.begin(), items.end());
	return {m(max_weight, n), items};
}
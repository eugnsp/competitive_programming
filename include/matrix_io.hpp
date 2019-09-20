// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include "io.hpp"
#include <cstddef>
#include <type_traits>

template<typename T = void, class Matrix, class Fn>
bool read_matrix(Matrix& mat, Fn fn)
{
	using S = typename std::conditional<std::is_void<T>::value, typename Matrix::Value, T>::type;

	for (std::size_t row = 0; row < mat.rows(); ++row)
		for (std::size_t col = 0; col < mat.cols(); ++col)
		{
			S s;
			if (!read(s))
				return false;
			mat(row, col) = fn(s);
		}

	return true;
}

template<class Matrix>
bool read_matrix(Matrix& mat)
{
	return read_matrix<typename Matrix::Value>(mat, [](const typename Matrix::Value& x) { return x; });
}

template<typename T = void, class Matrix, class Fn>
bool read_transposed_matrix(Matrix& mat, Fn fn)
{
	using S = typename std::conditional<std::is_void<T>::value, typename Matrix::Value, T>::type;

	for (std::size_t row = 0; row < mat.rows(); ++row)
		for (std::size_t col = 0; col < mat.cols(); ++col)
		{
			S s;
			if (!read(s))
				return false;
			mat(col, row) = fn(s);
		}

	return true;
}

template<class Matrix>
bool read_transposed_matrix(Matrix& mat)
{
	return read_transposed_matrix<typename Matrix::Value>(mat, [](const typename Matrix::Value& x) { return x; });
}

template<class Matrix>
bool write_matrix(Matrix& mat)
{
	for (std::size_t row = 0; row < mat.rows(); ++row)
	{
		for (std::size_t col = 0; col < mat.cols(); ++col)
			write(mat(row, col), ' ');
		write_ln();
	}

	return true;
}

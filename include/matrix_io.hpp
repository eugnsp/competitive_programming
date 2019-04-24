// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <type_traits>

template<typename T = void, class Matrix, class Fn>
bool read_matrix(Matrix& mat, Fn fn)
{
	using S = typename std::conditional<std::is_void<T>::value, typename Matrix::Type, T>::type;

	for (typename Matrix::Size row = 0; row < mat.rows(); ++row)
		for (typename Matrix::Size col = 0; col < mat.cols(); ++col)
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
	return read_matrix<typename Matrix::Type>(mat,
		[](const typename Matrix::Type& x) { return x; });
}

template<typename T = void, class Matrix, class Fn>
bool read_transposed_matrix(Matrix& mat, Fn fn)
{
	using S = typename std::conditional<std::is_void<T>::value, typename Matrix::Type, T>::type;

	for (typename Matrix::Size row = 0; row < mat.rows(); ++row)
		for (typename Matrix::Size col = 0; col < mat.cols(); ++col)
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
	return read_transposed_matrix<typename Matrix::Type>(mat,
		[](const typename Matrix::Type& x) { return x; });
}

template<class Matrix>
bool write_matrix(Matrix& mat)
{
	for (typename Matrix::Size row = 0; row < mat.rows(); ++row)
	{
		for (typename Matrix::Size col = 0; col < mat.cols(); ++col)
			write(mat(row, col), ' ');
		write_ln();
	}

	return true;
}

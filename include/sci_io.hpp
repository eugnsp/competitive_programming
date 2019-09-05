#pragma once
#include "matrix.hpp"
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <vector>

template<typename T>
std::ostream& operator<<(std::ostream& os, const Matrix<T>& mat)
{
	os << std::fixed << std::setprecision(4);
	for (std::size_t row = 0; row < mat.rows(); ++row)
	{
		for (std::size_t col = 0; col < mat.cols(); ++col)
			os << std::setw(7) << mat(row, col) << ' ';
		os << '\n';
	}

	return os;
}

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& vec)
{
	os << std::fixed << std::setprecision(4);
	for (auto v : vec)
		os << v << ' ';
	os << std::endl;

	return os;
}

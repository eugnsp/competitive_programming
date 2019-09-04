/*********************************************************************
Jacobi method
-------------
Chapter 5, problem 9

Implement the Jacobi eigenvalue algorithm to find eigenvalues and
eigenvectors of a real symmetric matrix.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "matrix.hpp"
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <vector>

template<typename T>
T off(const Matrix<T>& mat)
{
	assert(mat.rows() == mat.cols());
	const auto n = mat.rows();

	T res = 0;
	for (std::size_t row = 0; row < n - 1; ++row)
		for (std::size_t col = row + 1; col < n; ++col)
			res += std::abs(mat(row, col));

	return res;
}

template<typename T>
void rotate(Matrix<T>& mat, const std::size_t row1, const std::size_t col1, const std::size_t row2,
	const std::size_t col2, const T s, const T tau)
{
	const auto m1 = mat(row1, col1);
	const auto m2 = mat(row2, col2);
	mat(row1, col1) = m1 - s * (m2 + m1 * tau);
	mat(row2, col2) = m2 + s * (m1 - m2 * tau);
}

// Finds eigenvalues and eigenvectors of a real symmetric matrix using the Jacobi method;
// the algorithm is a simplified version of that described in "Linear algebra" (J.H.Wilkinson)
// and "Numerical recipes" (W.H.Press)
template<typename T>
void jacobi_eigenpairs(Matrix<T>& mat, Matrix<double>& vecs, std::vector<double>& vals, const double delta = 1e-8)
{
	assert(mat.rows() == mat.cols());
	const auto n = mat.rows();

	vecs.resize_and_fill(n, n, 0);
	vals.resize(n);

	for (std::size_t i = 0; i < n; i++)
	{
		vals[i] = mat(i, i);
		vecs(i, i) = 1;
	}

	constexpr unsigned int max_iters = 50u;
	unsigned int iter = 0;
	while (true)
	{
		if (off(mat) < delta * n * n)
			break;

		for (std::size_t row = 0; row < n - 1; row++)
			for (std::size_t col = row + 1; col < n; col++)
			{
				if (std::abs(mat(row, col)) < delta)
					continue;

				const auto theta = (vals[col] - vals[row]) / (2 * mat(row, col));
				const auto t = std::copysign(1 / (std::abs(theta) + std::hypot(1, theta)), theta);
				const auto cos = 1 / std::hypot(1, t);
				const auto sin = t * cos;
				const auto tau = sin / (1 + cos);
				const auto h = t * mat(row, col);

				vals[row] -= h;
				vals[col] += h;

				mat(row, col) = 0;
				for (std::size_t i = 0; i < row; i++)
					rotate(mat, i, row, i, col, sin, tau);
				for (std::size_t i = row + 1; i < col; i++)
					rotate(mat, row, i, i, col, sin, tau);
				for (std::size_t i = col + 1; i < n; i++)
					rotate(mat, row, i, col, i, sin, tau);

				for (std::size_t j = 0; j < n; j++)
					rotate(vecs, j, row, j, col, sin, tau);
			}

		if (++iter >= max_iters)
			std::runtime_error("Too many iterations");
	}
}

// Returns the Hilbert matrix of the given order
template<typename T>
Matrix<T> hilbert_matrix(const std::size_t n)
{
	Matrix<T> mat(n, n);
	for (std::size_t col = 0; col < n; ++col)
		for (std::size_t row = 0; row < n; ++row)
			mat(row, col) = T{1} / (1 + row + col);

	return mat;
}

// Returns the Frank matrix of the given order
template<typename T>
Matrix<T> frank_matrix(const std::size_t n)
{
	Matrix<T> mat(n, n);
	for (std::size_t col = 0; col < n; ++col)
		for (std::size_t row = 0; row < n; ++row)
			mat(row, col) = 1 + std::min(row, col);

	return mat;
}

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

void test(Matrix<double> mat)
{
	std::cout << "Matrix:\n" << mat << std::endl;

	Matrix<double> vecs;
	std::vector<double> vals;
	jacobi_eigenpairs(mat, vecs, vals);

	std::cout << "Eigenvalues:\n";
	std::cout << std::fixed << std::setprecision(7);

	for (auto v : vals)
		std::cout << v << ' ';
	std::cout << '\n' << std::endl;

	std::cout << "Eigenvectors:\n" << vecs << std::endl;
	std::cout << "-------------\n" << std::endl;
}

int main()
{
	test(hilbert_matrix<double>(4));
	test(frank_matrix<double>(4));

	return 0;
}

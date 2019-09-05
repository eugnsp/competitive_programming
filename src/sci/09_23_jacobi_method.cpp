/*********************************************************************
Jacobi method
-------------
Chapter 9, problem 23

Implement the iterative Jacobi method of solving linear systems.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "matrix.hpp"
#include "sci_io.hpp"
#include <cassert>
#include <cmath>
#include <cstddef>
#include <iomanip>
#include <iostream>
#include <stdexcept>
#include <utility>
#include <vector>

template<typename T>
T dist1(const std::vector<T>& x, const std::vector<T>& y)
{
	assert(x.size() == y.size());

	T diff = 0;
	for (std::size_t i = 0; i < x.size(); ++i)
		diff += std::abs(x[i] - y[i]);
	return diff;
}

// Computes y += mat * x
template<typename T>
void mul_add(const Matrix<T>& mat, const std::vector<T>& x, std::vector<T>& y)
{
	assert(mat.rows() == y.size());
	assert(mat.cols() == x.size());

	for (std::size_t j = 0; j < mat.cols(); ++j)
		for (std::size_t i = 0; i < mat.rows(); ++i)
			y[i] += mat(i, j) * x[j];
}

// Solves the linear system mat * sol = rhs using the Jacobi method
template<typename T>
unsigned int jacobi(Matrix<T> mat, std::vector<T> rhs, std::vector<T>& sol, const double delta = 1e-8)
{
	// To solve A x = b, iterate
	// 		x_{k+1} = B x_k + c,
	// where
	// 		B = -D^{-1} (A - D), c = D^{-1} b
	// with the preconditioner D = diag(A)

	assert(mat.rows() == mat.cols());
	assert(mat.rows() == rhs.size());
	assert(mat.rows() == sol.size());
	const auto n = mat.rows();

	std::vector<T> d(n); // = D^{-1}
	for (std::size_t i = 0; i < n; ++i)
		d[i] = 1 / std::exchange(mat(i, i), 0);

	for (std::size_t i = 0; i < n; ++i)
	{
		for (std::size_t j = 0; j < n; ++j)
			mat(i, j) *= -d[i];
		rhs[i] *= d[i];
	}

	std::vector<T> new_sol;

	constexpr unsigned int max_iters = 1'000u;
	unsigned int iter = 1;
	while (true)
	{
		new_sol = rhs;
		mul_add(mat, sol, new_sol);
		if (dist1(sol, new_sol) < delta)
			break;

		sol = new_sol;

		if (++iter >= max_iters)
			throw std::runtime_error("Too many iterations");
	}

	return iter;
}

int main()
{
	Matrix<double> mat(4, 4, {7, 1, 1, 2, 1, 6, -2, 3, 1, -2, 7, 4, 2, 3, 4, 6});
	std::vector<double> rhs{1, 2, 3, 4};
	std::vector<double> sol{0, 0, 0, 0};

	std::cout << "System matrix:\n";
	std::cout << mat << std::endl;

	std::cout << "Right-hand side:\n";
	std::cout << rhs << std::endl;

	std::cout << "Initial guess:\n";
	std::cout << sol << std::endl;

	const auto iter = jacobi(mat, rhs, sol);

	std::cout << "Solution after " << iter << " iterations:\n";
	std::cout << sol << std::endl;

	std::vector<double> rhs_check{0, 0, 0, 0};
	mul_add(mat, sol, rhs_check);

	std::cout << "Computed right-hand side:\n";
	std::cout << rhs_check << std::endl;

	return 0;
}

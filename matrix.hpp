// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include "position.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iosfwd>
#include <iomanip>
#include <vector>
#include <utility>

template<typename T, typename I = std::size_t>
class Matrix
{
private:
	using Container = std::vector<T>;
	using Reference = typename Container::reference;

public:
	Matrix() = default;

	Matrix(I rows, I cols)
		: data_(rows * cols), rows_(rows), cols_(cols)
	{ }

	Matrix(I rows, I cols, T value)
		: Matrix(rows, cols)
	{ 
		fill(value);
	}

	Matrix(const Matrix&) = default;
	Matrix(Matrix&&) = default;

	Matrix& operator=(const Matrix&) = default;
	Matrix& operator=(Matrix&&) = default;

	Reference operator()(I row, I col)
	{
		assert(row < rows_ && col < cols_);
		return data_[row + col * rows_];
	}

	T operator()(I row, I col) const
	{
		assert(row < rows_ && col < cols_);
		return data_[row + col * rows_];
	}

	Reference operator()(Position<I> pos)
	{
		return (*this)(pos.row, pos.col);
	}

	T operator()(Position<I> pos) const
	{
		return (*this)(pos.row, pos.col);
	}

	I rows() const
	{
		return rows_;
	}

	I cols() const
	{
		return cols_;
	}

	void resize(I rows, I cols)
	{ 
		rows_ = rows;
		cols_ = cols;
		data_.resize(rows_ * cols_);
	}

	void fill(T value)
	{
		std::fill(data_.begin(), data_.end(), value);
	}

	void resize_and_fill(I rows, I cols, T value)
	{
		resize(rows, cols);
		fill(value);
	}

	void zero()
	{
		fill(0);
	}

	void swap_rows(I row1, I row2)
	{ 
		assert(row1 < rows_ && row2 < rows_);
		assert(row1 != row2);

		for (I col = 0; col < cols_; ++col)
			std::swap((*this)(row1, col), (*this)(row2, col));
	}

	void swap_cols(I col1, I col2)
	{
		assert(col1 < cols_ && col2 < cols_);
		assert(col1 != col2);

		std::swap_ranges(
			data_.begin() + rows_ * col1,
			data_.begin() + rows_ * (col1 + 1),
			data_.begin() + rows_ * col2);
	}

	void swap(Matrix& other) noexcept
	{
		std::swap(data_, other.data_);
		std::swap(rows_, other.rows_);
		std::swap(cols_, other.cols_);
	}

private:
	Container data_;
	I rows_ = 0;
	I cols_ = 0;
};

//////////////////////////////////////////////////////////////////////////

template<typename T, typename I>
void swap(Matrix<T, I>& x, Matrix<T, I>& y) noexcept
{
	x.swap(y);
}

template<typename T, typename I>
Matrix<T, I> operator*(const Matrix<T, I>& x, const Matrix<T, I>& y)
{
	assert(x.cols() == y.rows());

	Matrix<T, I> res(x.rows(), y.cols(), 0);
	for (I j = 0; j < y.cols(); ++j)
		for (I i = 0; i < x.rows(); ++i)
			for (I k = 0; k < x.cols(); ++k)
				res(i, j) += x(i, k) * y(k, j);

	return res;
}

template<typename T, typename I>
Matrix<T, I> power(Matrix<T, I> x, unsigned long long power)
{
	assert(x.rows() == x.cols());

	Matrix<T, I> res(x.rows(), x.rows(), 0);
	for (I i = 0; i < res.rows(); ++i)
		res(i, i) = 1;

	while (power > 0)
	{
		if (power & 1u)
			res = res * x;

		x = x * x;
		power >>= 1;
	}

	return res;
}

template<typename S, typename T, typename I, class Transform>
void read_matrix(std::istream& in, Matrix<T, I>& x, Transform transform)
{
	for (I i = 0; i < x.rows(); ++i)
		for (I j = 0; j < x.cols(); ++j)
		{
			S s;
			in >> s;
			x(i, j) = transform(s);
		}
}

template<typename T, typename I>
void read_matrix(std::istream& in, Matrix<T, I>& x)
{
	read_matrix<T>(in, x, [](T v) { return v; });
}

template<typename T, typename I>
std::ostream& operator<<(std::ostream& out, const Matrix<T, I>& m)
{
	for (I i = 0; i < m.rows(); ++i)
	{
		for (I j = 0; j < m.cols(); ++j)
			out << std::setw(8) << m(i, j);
		out << '\n';
	}
	return out;
}

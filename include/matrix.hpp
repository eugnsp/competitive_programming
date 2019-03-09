// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include "io.hpp"
#include "position.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iosfwd>
#include <iomanip>
#include <vector>
#include <utility>

template<typename V, typename S = std::size_t>
class Matrix
{
public:
	using Type = V;
	using Size = S;

private:
	using Container = std::vector<Type>;
	using Reference = typename Container::reference;

public:
	Matrix() = default;

	Matrix(Size rows, Size cols) : data_(rows * cols), rows_(rows), cols_(cols)
	{}

	Matrix(Size rows, Size cols, const Type& value) : Matrix(rows, cols)
	{
		fill(value);
	}

	Matrix(const std::vector<std::vector<Type>>& data) :
		Matrix(static_cast<Size>(data.front().size()), static_cast<Size>(data.size()))
	{
		for (Size col = 0; col < cols(); ++col)
		{
			assert(data[col].size() == data.front().size());
			std::copy(data[col].begin(), data[col].end(), begin_col(col));
		}
	}

	Matrix(const Matrix&) = default;
	Matrix(Matrix&&) = default;

	Matrix& operator=(const Matrix&) = default;
	Matrix& operator=(Matrix&&) = default;

	Reference operator()(S row, S col)
	{
		assert(row < rows_ && col < cols_);
		return data_[row + col * rows_];
	}

	V operator()(S row, S col) const
	{
		assert(row < rows_ && col < cols_);
		return data_[row + col * rows_];
	}

	Reference operator()(Position<S> pos)
	{
		return (*this)(pos.row, pos.col);
	}

	V operator()(Position<S> pos) const
	{
		return (*this)(pos.row, pos.col);
	}

	typename Container::iterator begin_col(S col)
	{
		assert(col < cols_);
		return data_.begin() + rows_ * col;
	}

	typename Container::iterator end_col(S col)
	{
		return begin_col(col) + rows_;
	}

	typename Container::const_iterator begin_col(S col) const
	{
		assert(col < cols_);
		return data_.begin() + rows_ * col;
	}

	typename Container::const_iterator end_col(S col) const
	{
		return begin_col(col) + rows_;
	}

	S rows() const
	{
		return rows_;
	}

	S cols() const
	{
		return cols_;
	}

	void resize(S rows, S cols)
	{
		rows_ = rows;
		cols_ = cols;
		data_.resize(rows_ * cols_);
	}

	void fill(V value)
	{
		std::fill(data_.begin(), data_.end(), value);
	}

	void resize_and_fill(S rows, S cols, V value)
	{
		resize(rows, cols);
		fill(value);
	}

	void zero()
	{
		fill(0);
	}

	void swap_rows(S row1, S row2)
	{
		assert(row1 < rows_ && row2 < rows_);
		assert(row1 != row2);

		for (S col = 0; col < cols_; ++col)
			std::swap((*this)(row1, col), (*this)(row2, col));
	}

	void swap_cols(S col1, S col2)
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
	S rows_ = 0;
	S cols_ = 0;
};

//////////////////////////////////////////////////////////////////////////

template<typename V, typename S>
void swap(Matrix<V, S>& x, Matrix<V, S>& y) noexcept
{
	x.swap(y);
}

template<typename V, typename S>
Matrix<V, S> operator*(const Matrix<V, S>& x, const Matrix<V, S>& y)
{
	assert(x.cols() == y.rows());

	Matrix<V, S> res(x.rows(), y.cols(), 0);
	for (S j = 0; j < y.cols(); ++j)
		for (S i = 0; i < x.rows(); ++i)
			for (S k = 0; k < x.cols(); ++k)
				res(i, j) += x(i, k) * y(k, j);

	return res;
}

template<typename V, typename S>
Matrix<V, S> power(Matrix<V, S> x, unsigned long long power)
{
	assert(x.rows() == x.cols());

	Matrix<V, S> res(x.rows(), x.rows(), 0);
	for (S i = 0; i < res.rows(); ++i)
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

template<typename U, typename V, typename S, class Fn>
void read_tr(Matrix<V, S>& mat, Fn fn)
{
	for (S j = 0; j < mat.cols(); ++j)
		for (S i = 0; i < mat.rows(); ++i)
		{
			U s;
			read(s);
			mat(i, j) = fn(s);
		}
}

template<typename V, typename S>
void read_tr(Matrix<V, S>& mat)
{
	read_tr<V>(mat, [](V x) { return x; });
}

template<typename V, typename S>
void write(const Matrix<V, S>& m)
{
	for (S i = 0; i < m.rows(); ++i)
	{
		write(m(i, 0));
		for (S j = 1; j < m.cols(); ++j)
			write(' ', m(i, j));
		write_ln();
	}
}

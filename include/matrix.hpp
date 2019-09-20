// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include "matrix_io.hpp"
#include "position.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <initializer_list>
#include <iomanip>
#include <iosfwd>
#include <utility>
#include <vector>

template<typename T>
class Matrix
{
public:
	using Value = T;

	using Container = std::vector<Value>;
	using Reference = typename Container::reference;
	using Const_reference = typename Container::const_reference;

	using Col_iterator = typename Container::iterator;
	using Col_const_iterator = typename Container::const_iterator;

public:
	Matrix() = default;

	Matrix(std::size_t rows, std::size_t cols) : data_(rows * cols), rows_(rows), cols_(cols)
	{}

	Matrix(std::size_t rows, std::size_t cols, const Value& value) : Matrix(rows, cols)
	{
		fill(value);
	}

	Matrix(const std::vector<std::vector<Value>>& data) : Matrix(data.front().size(), data.size())
	{
		for (std::size_t col = 0; col < cols(); ++col)
		{
			assert(data[col].size() == data.front().size());
			std::copy(data[col].begin(), data[col].end(), begin_col(col));
		}
	}

	Matrix(std::size_t rows, std::size_t cols, std::initializer_list<Value> init) :
		data_(init), rows_(rows), cols_(cols)
	{}

	Matrix(const Matrix&) = default;
	Matrix(Matrix&&) = default;

	Matrix& operator=(const Matrix&) = default;
	Matrix& operator=(Matrix&&) = default;

	Reference operator()(std::size_t row, std::size_t col)
	{
		assert(row < rows_ && col < cols_);
		return data_[row + col * rows_];
	}

	Const_reference operator()(std::size_t row, std::size_t col) const
	{
		assert(row < rows_ && col < cols_);
		return data_[row + col * rows_];
	}

	Reference operator()(Position pos)
	{
		return (*this)(pos.row, pos.col);
	}

	Value operator()(Position pos) const
	{
		return (*this)(pos.row, pos.col);
	}

	const Container& data() const
	{
		return data_;
	}

	Col_iterator begin_col(std::size_t col)
	{
		assert(col < cols_);
		return data_.begin() + rows_ * col;
	}

	Col_iterator end_col(std::size_t col)
	{
		return begin_col(col) + rows_;
	}

	Col_const_iterator begin_col(std::size_t col) const
	{
		assert(col < cols_);
		return data_.begin() + rows_ * col;
	}

	Col_const_iterator end_col(std::size_t col) const
	{
		return begin_col(col) + rows_;
	}

	std::size_t rows() const
	{
		return rows_;
	}

	std::size_t cols() const
	{
		return cols_;
	}

	void resize(std::size_t rows, std::size_t cols)
	{
		rows_ = rows;
		cols_ = cols;
		data_.resize(rows_ * cols_);
	}

	void fill(const Value& value)
	{
		std::fill(data_.begin(), data_.end(), value);
	}

	void resize_and_fill(std::size_t rows, std::size_t cols, const Value& value)
	{
		resize(rows, cols);
		fill(value);
	}

	void swap_rows(std::size_t row1, std::size_t row2)
	{
		assert(row1 < rows_ && row2 < rows_);
		assert(row1 != row2);

		for (std::size_t col = 0; col < cols_; ++col)
			std::swap((*this)(row1, col), (*this)(row2, col));
	}

	void swap_cols(std::size_t col1, std::size_t col2)
	{
		assert(col1 < cols_ && col2 < cols_);
		assert(col1 != col2);

		std::swap_ranges(
			data_.begin() + rows_ * col1, data_.begin() + rows_ * (col1 + 1), data_.begin() + rows_ * col2);
	}

	void swap(Matrix& other) noexcept
	{
		std::swap(data_, other.data_);
		std::swap(rows_, other.rows_);
		std::swap(cols_, other.cols_);
	}

private:
	Container data_;
	std::size_t rows_ = 0;
	std::size_t cols_ = 0;
};

//////////////////////////////////////////////////////////////////////////

template<class Matrix>
bool is_inside_extents(const Matrix& matrix, Position pos)
{
	return pos.row < matrix.rows() && pos.col < matrix.cols();
}

template<typename T>
void swap(Matrix<T>& x, Matrix<T>& y) noexcept
{
	x.swap(y);
}

template<typename T>
Matrix<T> operator*(const Matrix<T>& x, const Matrix<T>& y)
{
	assert(x.cols() == y.rows());

	Matrix<T> res(x.rows(), y.cols(), 0);
	for (std::size_t j = 0; j < y.cols(); ++j)
		for (std::size_t i = 0; i < x.rows(); ++i)
			for (std::size_t k = 0; k < x.cols(); ++k)
				res(i, j) += x(i, k) * y(k, j);

	return res;
}

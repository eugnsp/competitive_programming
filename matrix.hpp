// Simple 2D matrix class
// ----------------------
//
// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <cstddef>
#include <utility>
#include <vector>
#include <algorithm>
#include <cassert>

template<typename Value>
class Matrix
{
private:
	using Container = std::vector<Value>;
	using Reference = typename Container::reference;

public:
	Matrix() = default;

	Matrix(std::size_t rows, std::size_t cols)
		: data_(rows * cols), rows_(rows), cols_(cols)
	{ }

	Matrix(std::size_t rows, std::size_t cols, Value value)
		: Matrix(rows, cols)
	{ 
		fill(value);
	}

	Matrix(const Matrix& other)
		: Matrix(other.rows(), other.cols())
	{
		std::copy(other.data_.begin(), other.data_.end(), data_.begin());
	}

	Matrix& operator=(const Matrix& other)
	{
		assert(rows_ == other.rows_ && cols_ == other.cols_);
		std::copy(other.data_.begin(), other.data_.end(), data_.begin());
		return *this;
	}

	Reference operator()(std::size_t row, std::size_t col)
	{
		assert(row < rows_ && col < cols_);
		return data_[row + col * rows_];
	}

	Value operator()(std::size_t row, std::size_t col) const
	{
		assert(row < rows_ && col < cols_);
		return data_[row + col * rows_];
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

	void fill(Value value)
	{
		std::fill(data_.begin(), data_.end(), value);
	}

	void resize_and_fill(std::size_t rows, std::size_t cols, Value value)
	{
		resize(rows, cols);
		fill(value);
	}

	void zero()
	{
		fill(0);
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
	std::size_t rows_ = 0;
	std::size_t cols_ = 0;
};

//////////////////////////////////////////////////////////////////////////

template<typename Value>
void swap(Matrix<Value>& x, Matrix<Value>& y) noexcept
{
	x.swap(y);
}
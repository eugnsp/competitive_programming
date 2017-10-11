// Simple 2D matrix class
// ----------------------
//
// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <cstddef>
#include <algorithm>
#include <memory>
#include <cassert>

template<typename Value>
class Matrix
{
public:
	Matrix(std::size_t rows, std::size_t cols)
		: data_(new Value[rows * cols]), rows_(rows), cols_(cols)
	{ }

	Matrix(std::size_t rows, std::size_t cols, Value value)
		: Matrix(rows, cols)
	{ 
		std::fill_n(data_.get(), rows_ * cols_, value);
	}

	Matrix(const Matrix& other)
		: Matrix(other.rows(), other.cols())
	{
		std::copy_n(other.data_.get(), rows_ * cols_, data_.get());
	}

	Matrix& operator=(const Matrix& other)
	{
		assert(rows_ == other.rows_ && cols_ == other.cols_);
		std::copy_n(other.data_.get(), rows_ * cols_, data_.get());
		return *this;
	}

	Value& operator()(std::size_t row, std::size_t col)
	{
		assert(row < rows_ && col < cols_);
		return data_[row + col * rows_];
		//return data_[col + row * cols_];
	}

	Value operator()(std::size_t row, std::size_t col) const
	{
		assert(row < rows_ && col < cols_);
		return data_[row + col * rows_];
		//return data_[col + row * cols_];
	}

	std::size_t rows() const
	{
		return rows_;
	}

	std::size_t cols() const
	{
		return cols_;
	}

private:
	std::unique_ptr<Value[]> data_;
	const std::size_t rows_;
	const std::size_t cols_;
};
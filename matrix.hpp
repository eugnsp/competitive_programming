// Simple 2D matrix
//
// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <cstddef>
#include <algorithm>
#include <memory>
#include <cassert>

template<typename T>
class Matrix
{
public:
	Matrix(std::size_t rows, std::size_t cols)
		: data_(new T[rows * cols]), rows_(rows), cols_(cols)
	{ }

	Matrix(std::size_t rows, std::size_t cols, T value)
		: Matrix(rows, cols)
	{ 
		std::fill(data_.get(), data_.get() + rows * cols, value);
	}

	T& operator()(std::size_t row, std::size_t col)
	{
		assert(row < rows_ && col < cols_);
		return data_[row + col * rows_];
	}

	T operator()(std::size_t row, std::size_t col) const
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

private:
	std::unique_ptr<T[]> data_;
	const std::size_t rows_;
	const std::size_t cols_;
};
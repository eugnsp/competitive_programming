// Simple 2D matrix class
// ----------------------
//
// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <cstddef>
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

private:
	Container data_;
	std::size_t rows_ = 0;
	std::size_t cols_ = 0;
};
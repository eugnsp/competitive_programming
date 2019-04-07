// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include "position.hpp"
#include "matrix_io.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iosfwd>
#include <iomanip>
#include <vector>
#include <utility>

template<typename T, typename S = std::size_t>
class Matrix
{
public:
	using Type = T;
	using Size = S;

	using Container = std::vector<Type>;
	using Reference = typename Container::reference;
	using Const_reference = typename Container::const_reference;

	using Col_iterator = typename Container::iterator;
	using Col_const_iterator = typename Container::const_iterator;

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

	Const_reference operator()(S row, S col) const
	{
		assert(row < rows_ && col < cols_);
		return data_[row + col * rows_];
	}

	Reference operator()(Position<S> pos)
	{
		return (*this)(pos.row, pos.col);
	}

	Type operator()(Position<S> pos) const
	{
		return (*this)(pos.row, pos.col);
	}

	const Container& data() const
	{
		return data_;
	}

	Col_iterator begin_col(S col)
	{
		assert(col < cols_);
		return data_.begin() + rows_ * col;
	}

	Col_iterator end_col(S col)
	{
		return begin_col(col) + rows_;
	}

	Col_const_iterator begin_col(S col) const
	{
		assert(col < cols_);
		return data_.begin() + rows_ * col;
	}

	Col_const_iterator end_col(S col) const
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

	void fill(const Type& value)
	{
		std::fill(data_.begin(), data_.end(), value);
	}

	void resize_and_fill(S rows, S cols, const Type& value)
	{
		resize(rows, cols);
		fill(value);
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

template<class Matrix>
bool is_inside_extents(const Matrix& matrix, Position<typename Matrix::Size> pos)
{
	return pos.row < matrix.rows() && pos.col < matrix.cols();
}

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

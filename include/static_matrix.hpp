// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include "position.hpp"
#include <array>
#include <cassert>
#include <cstddef>

template<typename T, std::size_t rows_, std::size_t cols_>
class Matrix
{
public:
	using Type = T;
	using Size = std::size_t;

public:
	Matrix() = default;

	Matrix(const Type& value)
	{
		fill(value);
	}

	template<typename... Ts>
	Matrix(const Ts&... values) : data_{values...}
	{}

	Type& operator[](Size index)
	{
		return data_[index];
	}

	const Type& operator[](Size index) const
	{
		assert(index < size());
		return data_[index];
	}

	Type& operator()(Size row, Size col)
	{
		assert(row < rows() && col < cols());
		return data_[index(row, col)];
	}

	const Type& operator()(Size row, Size col) const
	{
		assert(row < rows() && col < cols());
		return data_[index(row, col)];
	}

	Type& operator()(Position<Size> pos)
	{
		return (*this)(pos.row, pos.col);
	}

	const Type& operator()(Position<Size> pos) const
	{
		return (*this)(pos.row, pos.col);
	}

	void fill(const Type& value)
	{
		data_.fill(value);
	}

	static constexpr Size rows()
	{
		return rows_;
	}

	static constexpr Size cols()
	{
		return cols_;
	}

	static constexpr Size size()
	{
		return rows() * cols();
	}

	static Size index(Size row, Size col)
	{
		return row + rows() * col;
	}

	static Size index(Position<Size> pos)
	{
		return index(pos.row, pos.col);
	}

	static Position<Size> pos(Size index)
	{
		return {index % rows(), index / rows()};
	}

private:
	std::array<Type, rows_ * cols_> data_;
};

template<class Matrix>
bool is_inside_extents(Position<typename Matrix::Size> pos)
{
	return pos.row < Matrix::rows() && pos.col < Matrix::cols();
}

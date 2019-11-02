// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include "matrix_io.hpp"
#include "position.hpp"

#include <array>
#include <cassert>
#include <cstddef>

template<typename T, std::size_t rows_, std::size_t cols_>
class Matrix
{
public:
	using Value = T;
	using Size = std::size_t;

public:
	Matrix() = default;

	Matrix(const Value& value)
	{
		fill(value);
	}

	template<typename... Ts>
	Matrix(const Ts&... values) : data_{values...}
	{}

	Value& operator[](std::size_t index)
	{
		return data_[index];
	}

	const Value& operator[](std::size_t index) const
	{
		assert(index < size());
		return data_[index];
	}

	Value& operator()(std::size_t row, std::size_t col)
	{
		assert(row < rows() && col < cols());
		return data_[index(row, col)];
	}

	const Value& operator()(std::size_t row, std::size_t col) const
	{
		assert(row < rows() && col < cols());
		return data_[index(row, col)];
	}

	Value& operator()(Position pos)
	{
		return (*this)(pos.row, pos.col);
	}

	const Value& operator()(Position pos) const
	{
		return (*this)(pos.row, pos.col);
	}

	void fill(const Value& value)
	{
		data_.fill(value);
	}

	static constexpr std::size_t rows()
	{
		return rows_;
	}

	static constexpr std::size_t cols()
	{
		return cols_;
	}

	static constexpr std::size_t size()
	{
		return rows() * cols();
	}

	static std::size_t index(std::size_t row, std::size_t col)
	{
		return row + rows() * col;
	}

	static std::size_t index(Position pos)
	{
		return index(pos.row, pos.col);
	}

	static Position pos(std::size_t index)
	{
		return {index % rows(), index / rows()};
	}

private:
	std::array<Value, rows_ * cols_> data_;
};

template<class Matrix>
bool is_inside_extents(Position pos)
{
	return pos.row < Matrix::rows() && pos.col < Matrix::cols();
}

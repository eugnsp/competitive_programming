#pragma once
#include <cassert>
#include <cstddef>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <sstream>
#include <string>
#include <type_traits>

std::istream* istream;

bool ignore_line()
{
	return !!istream->ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

char peek()
{
	const auto ch = istream->peek();

	assert(istream->good());
	return static_cast<char>(ch);
}

bool read()
{
	return true;
}

template<typename T, typename... Ts>
bool read(T& arg, Ts&... args)
{
	return ((*istream) >> arg) && read(args...);
}

template<typename T1, typename T2>
bool read(std::pair<T1, T2>& pair)
{
	return read(pair.first, pair.second);
}

bool read_ln(std::string& str)
{
	return !!std::getline(*istream, str) && !str.empty();
}

bool read_ln_empty(std::string& str)
{
	return !!std::getline(*istream, str);
}

template<typename... Ts>
bool read_ln(Ts&... args)
{
	return read(args...) && ignore_line();
}

template<class T = void, class V, class Fn>
bool read_vec(std::size_t count, V& vec, Fn fn)
{
	using S = typename std::conditional<std::is_void<T>::value, typename V::value_type, T>::type;

	vec.reserve(vec.size() + count);
	for (std::size_t i = 0; i < count; ++i)
	{
		S y;
		if (!read(y))
			return false;
		vec.push_back(fn(y));
	}
	return true;
}

template<class V>
bool read_vec(std::size_t count, V& vec)
{
	using T = typename V::value_type;
	return read_vec<T>(count, vec, [](T x) { return x; });
}

template<typename T = void, class V, class Fn>
bool read_size_vec(V& vec, Fn fn)
{
	std::size_t size;
	read(size);
	if (size == 0)
		return false;

	vec.clear();
	return read_vec<T>(size, vec, fn);
}

template<class V>
bool read_size_vec(V& vec)
{
	std::size_t size;
	if (!read(size) || size == 0)
		return false;

	vec.clear();
	return read_vec(size, vec);
}

template<class V>
bool read_vec_ln(V& vec)
{
	using T = typename V::value_type;

	std::string str;
	if (!read_ln(str))
		return false;

	std::istringstream ss(str);

	T x;
	while (ss >> x)
		vec.push_back(x);

	return !vec.empty();
}

template<typename T, class Matrix, class Fn>
bool read_matrix(Matrix& mat, Fn fn)
{
	for (typename Matrix::Size row = 0; row < mat.rows(); ++row)
		for (typename Matrix::Size col = 0; col < mat.cols(); ++col)
		{
			T s;
			if (!read(s))
				return false;
			mat(row, col) = fn(s);
		}

	return true;
}

template<class Matrix>
bool read_matrix(Matrix& mat)
{
	return read_matrix<typename Matrix::Type>(mat,
		[](const typename Matrix::Type& x) { return x; });
}

void write()
{}

template<typename T, typename... Ts>
void write(const T& arg, const Ts&... args)
{
	std::cout << arg;
	write(args...);
}

template<typename... Ts>
void write_ln(const Ts&... args)
{
	write(args..., '\n');
}

template<class It, class Fn, typename Join>
void write_range(It first, It last, Fn fn, Join join)
{
	if (first == last)
		return;

	write(fn(*first++));
	while (first != last)
		write(join, fn(*first++));
}

template<class It, typename Join>
void write_range(It first, It last, Join join)
{
	using T = typename std::iterator_traits<It>::value_type;
	write_range(first, last, [](const T& x) { return x; }, join);
}

template<class Vec, class... Args>
void write_vec(const Vec& vec, Args... args)
{
	write_range(vec.begin(), vec.end(), args...);
}

template<class Matrix>
bool write_matrix(Matrix& mat)
{
	for (typename Matrix::Size row = 0; row < mat.rows(); ++row)
	{
		for (typename Matrix::Size col = 0; col < mat.cols(); ++col)
			write(mat(row, col), ' ');
		write_ln();
	}

	return true;
}


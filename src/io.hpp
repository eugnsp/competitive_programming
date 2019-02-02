#pragma once
#include <cassert>
#include <cstddef>
#include <iostream>
#include <limits>
#include <string>
#include <sstream>

bool ignore_line()
{
	return !!std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

bool read()
{
	return true;
}

template<typename T, typename... Ts>
bool read(T& arg, Ts&... args)
{
	return (std::cin >> arg) && read(args...);
}

template<typename T1, typename T2>
bool read(std::pair<T1, T2>& pair)
{
	return read(pair.first, pair.second);
}

bool read_ln(std::string& str)
{
	return !!std::getline(std::cin, str) && !str.empty();
}

bool read_ln_empty(std::string& str)
{
	return !!std::getline(std::cin, str);
}

template<typename... Ts>
bool read_ln(Ts&... args)
{
	return read(args...) && ignore_line();
}

template<class T, class V, class Fn>
bool read_vec(std::size_t count, V& vec, Fn fn)
{
	vec.reserve(vec.size() + count);
	for (std::size_t i = 0; i < count; ++i)
	{
		T y;
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

template<class V, class Fn>
bool read_size_vec(V& vec, Fn fn)
{
	std::size_t size;
	read(size);
	if (size == 0)
		return false;

	vec.clear();
	return read_vec(size, vec, fn);
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
	vec.clear();
	while (ss >> x)
		vec.push_back(x);

	return !vec.empty();
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

template<class V, class Fn, typename Join>
void write_vec(const V& vec, Fn fn, Join join)
{
	assert(!vec.empty());

	auto it = vec.begin();
	write(fn(*it++));

	while (it != vec.end())
		write(join, fn(*it++));
}

template<class V, typename Join>
void write_vec(const V& vec, Join join)
{
	using T = typename V::value_type;
	write_vec(vec, [](T x) { return x; }, join);
}

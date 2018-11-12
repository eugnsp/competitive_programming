// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <cstddef>
#include <istream>
#include <iterator>
#include <ostream>
#include <string>
#include <sstream>
#include <utility>
#include <vector>

template<class Input_it, class Func, typename Join = char>
void print_join_transform(std::ostream& out, Input_it first, Input_it last,
	Func func, Join join = ' ')
{
	if (first == last)
		return;
	
	out << func(*first++);
	while (first != last)
		out << join << func(*first++);
}

template<class Input_it, typename Join = char>
void print_join(std::ostream& out, Input_it first, Input_it last, Join join = ' ')
{
	using T = typename std::iterator_traits<Input_it>::value_type;
	print_join_transform(out, first, last, [](T x) { return x; }, join);
}

template<typename T, typename S, class Func>
bool read_vector(std::istream& in, std::size_t count, std::vector<S>& vec,
	Func func, bool append = false)
{
	if (!append)
		vec.clear();
	vec.reserve(vec.size() + count);
	
	for (std::size_t i = 0; i < count; ++i)
	{
		T y;
		if (!(in >> y))
			return false;
		vec.push_back(func(y));
	}

	return true;
}

template<typename T>
bool read_vector(std::istream& in, std::size_t count, std::vector<T>& vec,
	bool append = false)
{
	return read_vector<T>(in, count, vec, [](T x) { return x; }, append);
}

template<typename T>
bool read_vector_line(std::istream& in, std::vector<T>& vec)
{
	vec.clear();

	std::string str;
	if (!std::getline(in, str))
		return false;

	std::istringstream ss(str);

	T x;
	while (ss >> x)
		vec.push_back(x);

	return !vec.empty();
}

template<typename T1, typename T2>
std::istream& operator>>(std::istream& in, std::pair<T1, T2>& pair)
{
	in >> pair.first >> pair.second;
	return in;
}

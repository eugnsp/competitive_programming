// String distance and transform process
// -------------------------------------
//
// Goal: calculate the distance between two strings and the corresponding edit sequence.
//
// UVa ID: 526
// This file is covered by the LICENSE file in the root of this project.

#include "matrix.hpp"
#include <cstddef>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <cassert>

using T = unsigned int;

enum class Operations
{
	MATCH,
	REPLACE,
	INSERT,
	DELETE
};

struct M
{
	T distance;
	Operations operation;
};

std::vector<std::string> edit_sequence(
	const Matrix<M>& m, const std::string& st)
{
	std::vector<std::string> sequence;

	auto i = m.rows() - 1;
	auto j = m.cols() - 1;

	while (i != 0 || j != 0)
		switch (m(i, j).operation)
		{
		case Operations::REPLACE:
			assert(j > 0);
			sequence.push_back("Replace " + std::to_string(j) + ',' + st[j - 1]);
			[[fallthrough]]

		case Operations::MATCH:
			--i, --j;
			break;

		case Operations::INSERT:
			assert(j > 0);
			sequence.push_back("Insert " + std::to_string(j) + ',' + st[j - 1]);
			--j;
			break;

		case Operations::DELETE:
			sequence.push_back("Delete " + std::to_string(j + 1));
			--i;
		}

	std::reverse(sequence.begin(), sequence.end());
	return sequence;
}

template<typename T>
std::size_t index_of_min(T x, T y, T z)
{
	if (x <= y)
		return x <= z ? 0 : 2;
	else
		return y <= z ? 1 : 2;
}

// Returns the minimum number of operations (insertion, deletion and
// substitution) needed to transform the string (sf) into the string (st)
// and the corresponding edit sequence
std::pair<std::size_t, std::vector<std::string>> edit_distance(
	const std::string& sf, const std::string& st)
{
	const auto len_sf = static_cast<T>(sf.length());
	const auto len_st = static_cast<T>(st.length());

	// m(i, j).distance	=	the minimum number of operations needed to transform
	//						the prefix (sf[0 ... i-1]) into the prefix st[0 ... j-1])
	// m(i, j).operation =	the corresponding operation to get the cheapest sequence
	Matrix<M> m(len_sf + 1, len_st + 1);

	for (T i = 0; i <= len_sf; ++i)
	{
		m(i, 0).distance = i;
		m(i, 0).operation = Operations::DELETE;
	}

	for (T j = 1; j <= len_st; ++j)
	{
		m(0, j).distance = j;
		m(0, j).operation = Operations::INSERT;
	}

	for (T j = 1; j <= len_st; ++j)
		for (T i = 1; i <= len_sf; ++i)
		{
			const auto match = (sf[i - 1] == st[j - 1]);

			const auto dist_match_subst = m(i - 1, j - 1).distance + !match;
			const auto dist_delete = m(i - 1, j).distance + 1;
			const auto dist_insert = m(i, j - 1).distance + 1;

			switch (index_of_min(dist_match_subst, dist_delete, dist_insert))
			{
			case 0:
				m(i, j).distance = dist_match_subst;
				m(i, j).operation = match ? Operations::MATCH : Operations::REPLACE;
				break;

			case 1:
				m(i, j).distance = dist_delete;
				m(i, j).operation = Operations::DELETE;
				break;

			case 2:
				m(i, j).distance = dist_insert;
				m(i, j).operation = Operations::INSERT;
			}
		}

	return {m(len_sf, len_st).distance, edit_sequence(m, st)};
}

// <from string>
// <to string>

int main()
{	
	for (bool first = true; ; first = false)
	{
		std::string sf, st;
		std::getline(std::cin, sf);
		std::getline(std::cin, st);

		if (!std::cin)
			break;

		if (!first)
			std::cout << '\n';

		const auto dist = edit_distance(sf, st);
		std::cout << dist.first << '\n';
		for (std::size_t i = 0; i < dist.second.size(); ++i)
			std::cout << i + 1 << ' ' << dist.second[i] << '\n';
	}
	
	return 0;
}

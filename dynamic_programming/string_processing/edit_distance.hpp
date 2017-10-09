#pragma once
#include "matrix.hpp"
#include <cstddef>
#include <utility>
#include <vector>
#include <string>
#include <algorithm>
#include <cassert>

enum class Operations
{
	MATCH,
	REPLACE,
	INSERT,
	DELETE
};

template<typename T>
struct M
{
	T distance;
	Operations operation;
};

template<typename T>
struct Edit_operation
{
	T position_from;
	T position_to;
	Operations operation;
};

template<typename T>
std::size_t index_of_min(T x, T y, T z)
{
	if (x <= y)
		return x <= z ? 0 : 2;
	else
		return y <= z ? 1 : 2;
}

template<typename T>
void edit_distance_impl(Matrix<M<T>>& m, const std::string& sf, const std::string& st)
{
	assert(m.rows() == sf.length() + 1);
	assert(m.cols() == st.length() + 1);

	const auto len_sf = static_cast<T>(sf.length());
	const auto len_st = static_cast<T>(st.length());

	// m(i, j).distance	=	the minimum number of operations needed to transform
	//						the prefix (sf[0 ... i-1]) into the prefix st[0 ... j-1])
	// m(i, j).operation =	the corresponding operation to get the cheapest sequence

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
}

template<typename T>
std::vector<Edit_operation<T>> edit_sequence(const Matrix<M<T>>& m)
{
	std::vector<Edit_operation<T>> sequence;

	auto pos_from = static_cast<T>(m.rows() - 1);
	auto pos_to = static_cast<T>(m.cols() - 1);

	while (pos_from != 0 || pos_to != 0)
	{
		sequence.push_back({pos_from, pos_to, m(pos_from, pos_to).operation});

		switch (m(pos_from, pos_to).operation)
		{
		case Operations::REPLACE:
		case Operations::MATCH:
			--pos_from, --pos_to;
			break;

		case Operations::INSERT:
			--pos_to;
			break;

		case Operations::DELETE:
			--pos_from;
		}
	}

	std::reverse(sequence.begin(), sequence.end());
	return sequence;
}

// Returns the minimum number of operations (insertion, deletion and
// substitution) needed to transform the string (sf) into the string (st)
// and the corresponding edit sequence
template<typename T>
T edit_distance(const std::string& sf, const std::string& st)
{
	const auto len_sf = static_cast<T>(sf.length());
	const auto len_st = static_cast<T>(st.length());

	Matrix<M<T>> m(len_sf + 1, len_st + 1);
	edit_distance_impl(m, sf, st);

	return m(len_sf, len_st).distance;
}

template<typename T>
std::pair<T, std::vector<Edit_operation<T>>> edit_distance_and_sequence(
	const std::string& sf, const std::string& st)
{
	const auto len_sf = sf.length();
	const auto len_st = st.length();

	Matrix<M<T>> m(len_sf + 1, len_st + 1);
	edit_distance_impl(m, sf, st);

	return {m(len_sf, len_st).distance, edit_sequence(m)};
}

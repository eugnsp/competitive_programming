// Dynamic programming edit distance common routines
// -------------------------------------------------
//
// This file is covered by the LICENSE file in the root of this project.

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

struct Min_prefix_transform
{
	std::size_t distance;
	Operations operation;
};

struct Edit_operation
{
	std::size_t position_from;
	std::size_t position_to;
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

inline Matrix<Min_prefix_transform> edit_distance_impl(const std::string& sf, const std::string& st)
{
	const auto len_sf = sf.length();
	const auto len_st = st.length();

	// m(i, j).distance	=	the minimum number of operations needed to transform
	//						the prefix (sf[0 ... i-1]) into the prefix st[0 ... j-1])
	// m(i, j).operation =	the corresponding operation to get the cheapest sequence
	Matrix<Min_prefix_transform> m(len_sf + 1, len_st + 1);

	for (std::size_t i = 0; i <= len_sf; ++i)
	{
		m(i, 0).distance = i;
		m(i, 0).operation = Operations::DELETE;
	}

	for (std::size_t j = 1; j <= len_st; ++j)
	{
		m(0, j).distance = j;
		m(0, j).operation = Operations::INSERT;
	}

	for (std::size_t j = 1; j <= len_st; ++j)
		for (std::size_t i = 1; i <= len_sf; ++i)
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
		
	return m;
}

inline std::vector<Edit_operation> edit_sequence(const Matrix<Min_prefix_transform>& m)
{
	std::vector<Edit_operation> sequence;

	auto pos_from = m.rows() - 1;
	auto pos_to = m.cols() - 1;

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
inline std::size_t edit_distance(const std::string& sf, const std::string& st)
{
	const auto len_sf = sf.length();
	const auto len_st = st.length();

	const auto m = edit_distance_impl(sf, st);
	return m(len_sf, len_st).distance;
}

// Returns the minimum number of operations (insertion, deletion and
// substitution) needed to transform the string (sf) into the string (st)
// and the corresponding edit sequence
inline std::pair<std::size_t, std::vector<Edit_operation>> edit_distance_and_sequence(
	const std::string& sf, const std::string& st)
{
	const auto len_sf = sf.length();
	const auto len_st = st.length();

	const auto m = edit_distance_impl(sf, st);
	return {m(len_sf, len_st).distance, edit_sequence(m)};
}

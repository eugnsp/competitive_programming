/*********************************************************************
String distance and transform process
-------------------------------------
UVa ID: 005 26

String Distance is a non-negative integer that measures the distance
between two strings. Here we give the definition. A transform list is
a list of strings, where each string, except for the last one, can be
changed to the string followed by adding a character, deleting a
character or replacing a character. The length of a transform list
is the count of strings minus 1 (that is the count of operations to
transform these two strings). The distance between two strings is
the length of a transform list from one string to the other with the
minimal length. You are to write a program to calculate the distance
between two strings and give the corresponding transform list.

Input
-----
Input consists a sequence of string pairs, each string pair consists
two lines, each string occupies one line. The length of each string
will be no more than 80.

Output
------
For each string pair, you should give an integer to indicate the
length between them at the first line, and give a sequence of command
to transform string1 to string2. Each command is a line lead by
command count, then the command. A command must be
	Insert pos,value
	Delete pos
	Replace pos,value
where pos is the position of the string and poss hould be between 1
and the current length of the string (in "Insert" command, pos can be
1 greater than the length), and value is a character. Actually manyc
ommand lists can satisfy the request, but only one of them is required.
Print a blank line between consecutive datasets.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

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
unsigned int index_of_min(T x, T y, T z)
{
	if (x <= y)
		return (x <= z) ? 0 : 2;
	else
		return (y <= z) ? 1 : 2;
}

Matrix<Min_prefix_transform> edit_distance(const std::string& sf, const std::string& st)
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

std::vector<Edit_operation> edit_sequence(const Matrix<Min_prefix_transform>& m)
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
			[[fallthrough]];

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
std::pair<std::size_t, std::vector<Edit_operation>> edit_distance_and_sequence(
	const std::string& sf, const std::string& st)
{
	const auto len_sf = sf.length();
	const auto len_st = st.length();

	const auto m = edit_distance(sf, st);
	return {m(len_sf, len_st).distance, edit_sequence(m)};
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_ln(str_from_) && read_ln(str_to_);
	}

	virtual void solve(unsigned int i_case) override
	{
		if (i_case > 1)
			write_ln();

		const auto dist = edit_distance_and_sequence(str_from_, str_to_);
		write_ln(dist.first);

		std::size_t i = 1;
		for (auto& op : dist.second)
		{
			if (op.operation == Operations::MATCH)
				continue;

			write(i++, ' ');
			switch (op.operation)
			{
			case Operations::REPLACE:
				write("Replace ", op.position_to, ',', str_to_[op.position_to - 1]);
				break;

			case Operations::INSERT:
				write("Insert ", op.position_to, ',', str_to_[op.position_to - 1]);
				break;

			case Operations::DELETE:
				write("Delete ", op.position_to + 1);
				break;
			}
			write_ln();
		}
	}

private:
	std::string str_from_;
	std::string str_to_;
};



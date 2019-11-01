/*********************************************************************
String computer
---------------
UVa ID: 001 64

Extel have just brought out their newest computer, a string processing
computer dubbed the X9091. It is hoped that it will have some value in
cryptography and related fields. (It is rumoured that the Taiwanese
are working on a clone that will correct Stage 1 essays, but we will
ignore such vapourware). This computer will accept input strings and
produce output strings from them, depending on the programs loaded
into them at the time. The chip is the ultimate in RISC technology -
it has only three transformation instructions:
	Delete a character at a particular position.
	Insert a character at a particular position.
	Change the character at a particular position
	to a different character.
Programs for this machine are written in a form of machine code where
each instruction has the format "ZXdd" - Z represents the code for
the instruction (D, I or C), X is a character and dd representsa two
digit number. A program is terminated by a special halt instruction
consisting of the letter "E". Note that each instruction works on
the string in memory at the time the instruction is executed. To see
how this all works consider the following example. It is desired to
transform the string "abcde" to the string "bcgfe". This could be
achieved by a series of Change commands, but is not minimal. The
following program is better.
			abcde
	Da01  	bcde	% note the "a" is necessary because
					  it is checked by the hardware
	Cg03  	bcge
	If04	bcgfe
	E		bcgfe	% terminates the program
Write a program that will read in two strings (the input string and
the target string) and will produce a minimal X9091 program necessary
to transform the input string into the target string. Since there may
be multiple solutions, only one should be produced. Any solution that
satisfies these criteria will be accepted.

Input
-----
Input will consist of a series of lines, each line containing two
strings separated by exactly one space. The strings will consist of
no more than 20 lower case characters. The file will be terminated
by a line consisting of a single "#".

Output
------
Output will consist of a series of lines, one for each line of the
input. Each will consist of a program in X9091 language.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iomanip>
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

std::vector<Edit_operation> edit_sequence(const std::string& sf, const std::string& st)
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

	std::vector<Edit_operation> sequence;

	auto pos_from = len_sf;
	auto pos_to = len_st;
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

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(str_from_, str_to_) && str_from_ != "#";
	}

	virtual void solve(unsigned int) override
	{
		const auto seq = edit_sequence(str_from_, str_to_);

		write(std::setfill('0'));
		for (auto& op : seq)
			switch (op.operation)
			{
			case Operations::REPLACE:
				write('C', str_to_[op.position_to - 1], std::setw(2), op.position_to);
				break;

			case Operations::INSERT:
				write('I', str_to_[op.position_to - 1], std::setw(2), op.position_to);
				break;

			case Operations::DELETE:
				write('D', str_from_[op.position_from - 1], std::setw(2), op.position_to + 1);
			}

		write_ln('E');
	}

private:
	std::string str_from_;
	std::string str_to_;
};

MAIN

/*********************************************************************
Whatfix notation
----------------
UVa ID: 003 72

There are three traversal methods commonly used in compilers and
calculators: prefix, infix, postfix. For example, a single expression
can be written in each form
	infix:    a + b * c
	prefix:   + a * b c
	postfix:  a b c * +
Note that prefix and postfix ARE NOT mirror images of each other!
The advantage of prefix and postfix notations is that parentheses
are unnecessary to prevent ambiguity. In our traversal the following
symbols are operators with precedence rules going from highest
to lowest:
	$		exponentiation
	* /		multiply and divide
	+ -		add and subtract
	& |		AND and OR
	!		NOT

Input
-----
You are given two strings. The first string is the infix version
of the expression. The second string isthe prefix version of the
expression. Determine the postfix version of the expression and
print it out ona single line. All input will be single characters
separated by a space.

Output
------
Output must be the same, single characters separated by a space.
There are no special sentinelsidentifying the end of the data.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <string>
#include <string_view>

void prefix_infix_to_postfix_impl(std::string_view prefix,
                                  std::string_view infix,
								  std::string& postfix)
{
	if (prefix.empty())
		return;

	const auto left_len = infix.find(prefix.front());
	assert(left_len != std::string::npos);

	prefix_infix_to_postfix_impl(prefix.substr(1, left_len), infix.substr(0, left_len), postfix);
	prefix_infix_to_postfix_impl(prefix.substr(left_len + 1), infix.substr(left_len + 1), postfix);

	postfix.push_back(prefix.front());
}

std::string prefix_infix_to_postfix(const std::string& prefix, const std::string& infix)
{
	std::string postfix;
	prefix_infix_to_postfix_impl(prefix, infix, postfix);
	return postfix;
}

class CP : public CP3
{
private:
	virtual void read_input() override
	{
		std::string str;

		read_ln(str);
		infix_expr_.clear();
		std::remove_copy(str.begin(), str.end(), std::back_inserter(infix_expr_), ' ');

		read_ln(str);
		prefix_expr_.clear();
		std::remove_copy(str.begin(), str.end(), std::back_inserter(prefix_expr_), ' ');
	}

	virtual void solve() override
	{
		auto postfix_expr = prefix_infix_to_postfix(prefix_expr_, infix_expr_);

		write("INFIX   => ");
		write_range(infix_expr_.begin(), infix_expr_.end(), ' ');
		write_ln();

		write("PREFIX  => ");
		write_range(prefix_expr_.begin(), prefix_expr_.end(), ' ');
		write_ln();

		write("POSTFIX => ");
		write_range(postfix_expr.begin(), postfix_expr.end(), ' ');
		write_ln();
	}

private:
	std::string infix_expr_;
	std::string prefix_expr_;
};

MAIN

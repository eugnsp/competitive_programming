/*********************************************************************
Equation
--------
UVa ID: 007 27

Write a program that changes an infix expression to a postfix
expression according to the following specifications.

Input
-----
1. The infix expression to be converted is in the input file in the
format of one character per line, with a maximum of 50 lines in the
file. For example, (3+2)*5 would be in the form:
(
3
+
2
)
*
5
2. The input starts with an integer on a line by itself indicating
the number of test cases. Several infix expressions follows, preceded
by a blank line.
3. The program will only be designed to handle the binary operators
"+", "-", "*", "/".
4. The operands will be one digit numerals.
5. The operators "*" and "/" have the highest priority. The operators
"+" and "-" have the lowest priority. Operators at the same precedence
level associate from left to right. Parentheses act as grouping
symbols that override the operator priorities.
6. Each testcase will be an expression with valid syntax.

Output
------
The output file will have each postfix expression all on one line.
Print a blank line between different expressions.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <stack>
#include <string>

bool is_digit(char ch)
{
	return '0' <= ch && ch <= '9';
}

bool is_operator(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

bool is_open_paren(char ch)
{
	return ch == '(';
}

bool is_close_paren(char ch)
{
	return ch == ')';
}

// Returns the operator precedence; higher value corresponds to higher precedence
unsigned char operator_precedence(char ch)
{
	assert(is_operator(ch));
	return (ch == '*' || ch == '/');
}

std::string infix_to_postfix(const std::string& infix)
{
	// Shunting-yard algorithm

	std::stack<char> operators;
	std::string postfix;

	for (auto it = infix.begin(); it != infix.end(); ++it)
	{
		if (is_digit(*it))
			postfix.push_back(*it);
		else if (is_open_paren(*it))
			operators.push(*it);
		else if (is_close_paren(*it))
		{
			while (!operators.empty() && !is_open_paren(operators.top()))
			{
				postfix.push_back(operators.top());
				operators.pop();
			}

			if (!operators.empty() && is_open_paren(operators.top()))
				operators.pop();
		}
		else if (is_operator(*it))
		{
			while (!operators.empty() && !is_open_paren(operators.top()) &&
				   operator_precedence(operators.top()) >= operator_precedence(*it))
			{
				postfix.push_back(operators.top());
				operators.pop();
			}

			operators.push(*it);
		}
	}

	while (!operators.empty())
	{
		postfix.push_back(operators.top());
		operators.pop();
	}

	return postfix;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		if (infix_expr_.empty())
			ignore_line();

		infix_expr_.clear();

		std::string str;
		while (read_ln_non_empty(str))
			infix_expr_.push_back(str.front());
	}

	virtual void solve(unsigned int i_case) override
	{
		if (i_case > 1)
			write_ln();

		write_ln(infix_to_postfix(infix_expr_));
	}

private:
	std::string infix_expr_;
};

MAIN


/*********************************************************************
Nesting a bunch of brackets
---------------------------
UVa ID: 005 51

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <cstddef>
#include <stack>
#include <string>
#include <utility>

enum class Bracket_type
{
	ROUND,
	SQUARE,
	CURLY,
	POINTY,
	ASTERISK
};

Bracket_type get_bracket_type(char ch)
{
	if (ch == '[' || ch == ']')
		return Bracket_type::SQUARE;
	if (ch == '{' || ch == '}')
		return Bracket_type::CURLY;
	if (ch == '<' || ch == '>')
		return Bracket_type::POINTY;
	if (ch == '(' || ch == ')')
		return Bracket_type::ROUND;

	return Bracket_type::ASTERISK;
}

std::pair<bool, std::size_t> check_valid_bracketing(const std::string& expr)
{
	std::stack<Bracket_type> stack;
	std::size_t len = 1;

	for (auto it = expr.begin(); it != expr.end(); ++it, ++len)
	{
		switch (*it)
		{
		case '(':
			if (it + 1 != expr.end() && *(it + 1) == '*')
				++it;
			[[fallthrough]];

		case '[':
		case '{':
		case '<':
			stack.push(get_bracket_type(*it));
			break;

		case ']':
		case '}':
		case '>':
		case ')':
			if (stack.empty() || stack.top() != get_bracket_type(*it))
				return {false, len};
			stack.pop();
			break;

		case '*':
			if (it + 1 != expr.end() && *(it + 1) == ')')
			{
				if (stack.empty())
					return {false, len};

				auto ch = stack.top();
				if (ch != Bracket_type::ASTERISK)
					return {false, len};
				stack.pop();
				++it;
			}
		}
	}

	return {stack.empty(), len};
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_ln(expr_);
	}

	virtual void solve(unsigned int) override
	{
		auto r = check_valid_bracketing(expr_);
		if (r.first)
			write_ln("YES");
		else
			write_ln("NO ", r.second);
	}

private:
	std::string expr_;
};

MAIN

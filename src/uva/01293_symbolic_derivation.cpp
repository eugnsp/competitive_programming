/*********************************************************************
Symbolic derivation
-------------------
UVa ID: 012 93

Write a program that performs symbolic derivation f'(x) = df(x)/dx
of a given function f(x). The function f(x) is defined by an
expression which may contain the following operations:
	"+" (addition),
	"-" (subtraction),
	"*" (multiplication),
	"/" (division), and
	"ln" (natural logarithm).
Besides, the operands may be the variable x and numerical constants.
The expression may contain arbitrarily nested sub-expressions in
parentheses ( ). The expression is given in a usual, in x form, such
as: (2*ln(x+1.7)-x*x)/((-7)+3.2*x*x)+(x+3*x)*x. Numerical constants
have the form "d.d", with an optional sign (+ or -), where the number
of digits both in integer and decimal parts are arbitrary.

Input
-----
The input is a textual file which has one f(x) definition per line.
The input lines do not have blanks. The input expression is
guaranteed to be correct (no syntax error can occur).

Output
------
The output should contain lines with corresponding symbolic derivations
f' = df/dx, one line for each f. The strings representing f(x) and
f'(x) are guaranteed to have no more than 100 characters. The output
expression should be written in in x form. It should not be optimized
for human reading. This means, it can contain redundancies, such as
"0 * x", "1 * x", "0 + x", etc. The derivation should be performed
using the following rules:
1. The operators "*" and "/" are of higher priority than the operators
"+" and "-". Parentheses may change the priorities as usually.
2. The operators "+", "-", "*", and "/" are left-associative.
3. The rules for derivation are: (a + b)' = a' + b', (a - b)' = a' - b',
(a - b)' = (a' * b + a * b'), (a / b) = (a' * b - a * b') / b^2. Note:
use b^2 and not (b * b) for presentation. ln(a)' = (a') / (a), x' = 1,
const' = 0.
4. While producing the symbolic derivation, use parentheses for output
strictly as stated in the previous rule. Do not perform presentation
optimizations, such as 0 * a = 0, 1 * a = a, etc.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <cstddef>
#include <memory>
#include <stack>
#include <string>
#include <utility>

struct Node;
using Node_ptr = std::shared_ptr<Node>;

enum class Node_type
{
	VAR,
	NUMBER,
	OPERATOR,
	FUNC,
	EXP
};

enum class Token_type
{
	VAR,
	NUMBER,
	OPERATOR,
	FUNC,
	OPEN_PAREN,
	CLOSE_PAREN,
	NONE
};

struct Node
{
	Node_type type;
	std::string value;
	std::size_t n_parens; // Number of parentheses enclosing this node

	Node_ptr left;
	Node_ptr right;

	Node(Node_type type, std::string value, std::size_t n_parens,
	     Node_ptr left = {}, Node_ptr right = {})
		: type(type), value(std::move(value)), n_parens(n_parens),
		  left(std::move(left)), right(std::move(right))
	{}

	template<typename... Ts>
	static Node_ptr make(Ts&&... args)
	{
		return std::make_shared<Node>(std::forward<Ts>(args)...);
	}

	template<typename... Ts>
	static Node_ptr make_operator(Ts&&... args)
	{
		return make(Node_type::OPERATOR, std::forward<Ts>(args)...);
	}
};

struct Token
{
	Token_type type;
	std::string value;

	Token(Token_type type, std::string value = {}) : type(type), value(std::move(value))
	{}
};

class Tokenizer
{
public:
	Tokenizer(const std::string& expr) : expr_(expr)
	{}

	template<class Fn>
	void for_each(Fn fn)
	{
		Token_type prev_token = Token_type::NONE;

		auto it = expr_.begin();
		while (it != expr_.end())
		{
			if (*it == 'x')
				fn(Token{prev_token = Token_type::VAR, "x"});
			else if (*it == '(')
				fn(Token{prev_token = Token_type::OPEN_PAREN});
			else if (*it == ')')
				fn(Token{prev_token = Token_type::CLOSE_PAREN});
			else if (*it == 'l')
			{
				++it;
				assert(*it == 'n');
				fn(Token{prev_token = Token_type::FUNC, "ln"});
			}
			else if (can_be_followed_by_operator(prev_token) && is_operator(*it))
				fn(Token{prev_token = Token_type::OPERATOR, {*it}});
			else if (is_digit_or_dot(*it) || *it == '-')
			{
				const auto start = it;
				do
					++it;
				while (it != expr_.end() && is_digit_or_dot(*it));
				fn(Token{prev_token = Token_type::NUMBER, std::string(start, it)});
				continue;
			}

			++it;
		}
	}

private:
	static bool is_digit_or_dot(char ch)
	{
		return ('0' <= ch && ch <= '9') || ch == '.';
	}

	static bool is_operator(char ch)
	{
		return ch == '+' || ch == '-' || ch == '*' || ch == '/';
	}

	// Returns true if the token of the given type can be followed
	// by a binary operator
	static bool can_be_followed_by_operator(Token_type type)
	{
		return type != Token_type::NONE && type != Token_type::OPERATOR &&
			   type != Token_type::OPEN_PAREN;
	}

private:
	const std::string& expr_;
};

class Parser
{
public:
	static Node_ptr parse(const std::string& expr)
	{
		Nodes_stack nodes;
		Tokens_stack tokens;

		Tokenizer tokenizer{expr};
		tokenizer.for_each([&](const Token& token) {
			switch (token.type)
			{
			case Token_type::VAR:
				add_node(nodes, Node_type::VAR, token.value, 0);
				break;

			case Token_type::NUMBER:
				add_node(nodes, Node_type::NUMBER, token.value, 0);
				break;

			case Token_type::OPERATOR:
				while (!tokens.empty() && tokens.top().type == Token_type::OPERATOR &&
					   operator_precedence(tokens.top()) >= operator_precedence(token))
					compose_node(nodes, tokens);

				[[fallthrough]];

			case Token_type::FUNC:
				[[fallthrough]];

			case Token_type::OPEN_PAREN:
				tokens.push(token);
				break;

			case Token_type::CLOSE_PAREN:
				while (!tokens.empty() && tokens.top().type != Token_type::OPEN_PAREN)
					compose_node(nodes, tokens);

				assert(!tokens.empty());
				tokens.pop();
				++nodes.top()->n_parens;

				if (!tokens.empty() && tokens.top().type == Token_type::FUNC)
					compose_node(nodes, tokens);
			}
		});

		while (!tokens.empty())
			compose_node(nodes, tokens);

		return std::move(nodes.top());
	}

private:
	using Nodes_stack = std::stack<Node_ptr>;
	using Tokens_stack = std::stack<Token>;

	// Returns the operator precedence; higher value corresponds to higher precedence
	static unsigned char operator_precedence(const Token& token)
	{
		assert(token.type == Token_type::OPERATOR);
		return (token.value == "*" || token.value == "/");
	}

	template<typename... Ts>
	static void add_node(Nodes_stack& nodes, Ts&&... args)
	{
		nodes.push(Node::make(std::forward<Ts>(args)...));
	}

	static void compose_node(Nodes_stack& nodes, Tokens_stack& tokens)
	{
		const auto& token = tokens.top();
		if (token.type == Token_type::FUNC)
		{
			auto node = std::move(nodes.top());
			nodes.pop();
			add_node(nodes, Node_type::FUNC, token.value, 0, std::move(node));
		}
		else if (token.type == Token_type::OPERATOR)
		{
			auto right = std::move(nodes.top());
			nodes.pop();
			auto left = std::move(nodes.top());
			nodes.pop();
			add_node(nodes, Node_type::OPERATOR, token.value, 0, std::move(left), std::move(right));
		}
		tokens.pop();
	}
};

Node_ptr derivative(const Node& node)
{
	if (node.type == Node_type::VAR)
		return Node::make(Node_type::NUMBER, "1", node.n_parens);

	if (node.type == Node_type::NUMBER)
		return Node::make(Node_type::NUMBER, "0", node.n_parens);

	if (node.value == "+" || node.value == "-")
		return Node::make_operator(
			node.value, node.n_parens, derivative(*node.left), derivative(*node.right));

	if (node.value == "*" || node.value == "/")
	{
		const auto& a = node.left;
		const auto& b = node.right;

		auto ap_b = Node::make_operator("*", 0, derivative(*a), b);
		auto a_bp = Node::make_operator("*", 0, a, derivative(*b));

		if (node.value == "*")
			return Node::make_operator("+", node.n_parens + 1, std::move(ap_b), std::move(a_bp));
		else
			return Node::make_operator("/", node.n_parens,
				Node::make_operator("-", 1, std::move(ap_b), std::move(a_bp)),
				Node::make(Node_type::EXP, "2", 0, b));
	}

	if (node.value == "ln")
	{
		const auto& a = node.left;
		return Node::make_operator("/", node.n_parens, derivative(*a), Node::make(*a));
	}

	assert(false);
}

std::string to_string(const Node_ptr& node)
{
	if (!node)
		return {};

	std::string str(node->n_parens, '(');

	if (node->right)
	{
		str += to_string(node->left);
		auto right = to_string(node->right);

		// A const with a unary minus: "...+-const" -> "...-const"
		if (node->value == "+" && right.front() == '-')
			str += '-' + right.substr(1);
		else
			str += node->value + right;
	}
	else if (node->type == Node_type::EXP)
		str += to_string(node->left) + '^' + node->value;
	else
		str += node->value + to_string(node->left);

	str.append(node->n_parens, ')');
	return str;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_ln_non_empty(func_);
	}

	virtual void solve(unsigned int) override
	{
		auto f_tree = Parser::parse(func_);
		auto df_tree = derivative(*f_tree);

		write_ln(to_string(df_tree));
	}

private:
	std::string func_;
};

MAIN

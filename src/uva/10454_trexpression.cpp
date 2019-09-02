/*********************************************************************
Trexpression
------------
UVa ID: 104 54

An algebraic expression can be represented by a tree. We can evaluate
the expression by traversing the corresponding tree. The tree
representation of an algebraic expression is not unique. Consider
an example: "1 + 2 + 3 * 4". It can be represented by two trees. In
the first representation, the evaluation order will be: 3 * 4 = 12;
2 + 12 =14; 1 + 14 = 15. And in the 2nd representation, the expression
will be evaluated like: 1 + 2 = 3; 3 * 4 =12; 3 + 12 = 15. Both
representations produce correct result. In this problem, we will
consider simple algebraic expressions consist of digits, "+", "*" and
parentheses. The expression will follow the normal algebraic rule.
You have to find out the number of tree representations which will
correctly evaluate the expression.

Input
-----
Each line in the input file contains an algebric expression consists
of single digit numbers, parentheses, addition and multiplication
operators. The expression will be syntactically correct and its length
will not exceed 130. There will be at least one operator and not more
than 35 operators in the expression. Input is terminated by EOF.

Output
------
For each expression you should print the number of tree
representations which will correctly evaluatethe expression in a line.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <array>
#include <cassert>
#include <memory>
#include <stack>
#include <utility>
#include <vector>

struct Node;
using Node_ptr = std::unique_ptr<Node>;

enum class Node_type
{
	NUMBER,
	OPERATOR
};

enum class Token_type
{
	NUMBER,
	OPERATOR,
	OPEN_PAREN,
	CLOSE_PAREN,
	NONE
};

struct Node
{
	Node_type type;
	char value;
	bool parenthesized = false;

	Node_ptr left;
	Node_ptr right;

	Node(Node_type type, char value = 0, Node_ptr left = {}, Node_ptr right = {}) :
		type(type), value(value), left(std::move(left)), right(std::move(right))
	{}
};

struct Token
{
	Token_type type;
	char value;

	Token(Token_type type, char value = 0) : type(type), value(value)
	{}
};

template<class Fn>
void for_each_token(const std::string& expr, Fn fn)
{
	Token_type prev_token = Token_type::NONE;

	auto it = expr.begin();
	while (it != expr.end())
	{
		if (*it == '(')
			fn(Token{prev_token = Token_type::OPEN_PAREN});
		else if (*it == ')')
			fn(Token{prev_token = Token_type::CLOSE_PAREN});
		else if (*it == '+' || *it == '*')
			fn(Token{prev_token = Token_type::OPERATOR, *it});
		else if ('0' <= *it && *it <= '9')
		{
			while (it != expr.end() && '0' <= *it && *it <= '9')
				++it;
			fn(Token{prev_token = Token_type::NUMBER});
			continue;
		}

		++it;
	}
}

class Parser
{
public:
	static Node_ptr parse(const std::string& expr)
	{
		Nodes_stack nodes;
		Tokens_stack tokens;

		for_each_token(expr, [&](const Token& token) {
			switch (token.type)
			{
			case Token_type::NUMBER:
				add_node(nodes, Node_type::NUMBER);
				break;

			case Token_type::OPERATOR:
				while (!tokens.empty() && tokens.top().type == Token_type::OPERATOR &&
					   operator_precedence(tokens.top()) >= operator_precedence(token))
					compose_node(nodes, tokens);

				[[fallthrough]];

			case Token_type::OPEN_PAREN:
				tokens.push(token);
				break;

			case Token_type::CLOSE_PAREN:
				while (!tokens.empty() && tokens.top().type != Token_type::OPEN_PAREN)
					compose_node(nodes, tokens);

				assert(!tokens.empty());
				tokens.pop();
				nodes.top()->parenthesized = true;
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
		return (token.value == '*');
	}

	template<typename... Ts>
	static void add_node(Nodes_stack& nodes, Ts&&... args)
	{
		nodes.push(std::make_unique<Node>(std::forward<Ts>(args)...));
	}

	static void compose_node(Nodes_stack& nodes, Tokens_stack& tokens)
	{
		const auto& token = tokens.top();
		if (token.type == Token_type::OPERATOR)
		{
			auto right = std::move(nodes.top());
			nodes.pop();
			auto left = std::move(nodes.top());
			nodes.pop();
			add_node(nodes, Node_type::OPERATOR, token.value, std::move(left), std::move(right));
		}
		tokens.pop();
	}
};

// Returns the Catalan numbers (C_0, ..., C_36)
auto catalan_numbers()
{
	std::array<unsigned long long, 37> catalan{}; // C_36 is the last that fits into ULL
	catalan[0] = 1;
	catalan[1] = 1;
	catalan[2] = 2;

	for (unsigned int i = 3; i < catalan.size(); ++i)
		for (unsigned int j = 0; j < i; ++j)
			catalan[i] += catalan[j] * catalan[i - 1 - j];

	return catalan;
}

template<typename T>
void compute_compontent_sizes(const Node_ptr& node, char parent_operator, std::vector<T>& compontent_sizes)
{
	if (!node || node->type == Node_type::NUMBER)
		return;

	const auto is_new_component = (node->parenthesized || node->value != parent_operator);
	if (is_new_component)
		compontent_sizes.push_back(1);
	else
		++compontent_sizes.back();

	compute_compontent_sizes(node->left, node->value, compontent_sizes);
	compute_compontent_sizes(node->right, node->value, compontent_sizes);
}

unsigned long long count_tree_representations(const Node_ptr& node)
{
	std::vector<unsigned int> compontent_sizes;
	compute_compontent_sizes(node, 0, compontent_sizes);

	unsigned long long n = 1;
	static auto catalan = catalan_numbers();
	for (auto nc : compontent_sizes)
		n *= catalan[nc];

	return n;
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_ln_non_empty(expr_);
	}

	virtual void solve(unsigned int) override
	{
		auto expr_tree = Parser::parse(expr_);
		write_ln(count_tree_representations(expr_tree));
	}

private:
	std::string expr_;
};

MAIN


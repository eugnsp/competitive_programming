/*********************************************************************
Generate parentheses
--------------------

For the given number of pairs of parentheses, generate all
combinations of well-formed parentheses.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cstddef>
#include <string>

class Parentheses_generator
{
public:
	Parentheses_generator(std::size_t n_pairs, char open = '(', char close = ')') :
		n_pairs_(n_pairs), open_(open), close_(close)
	{}

	template<class Fn>
	void operator()(Fn&& fn) const
	{
		generate(fn);
		str_.clear();
	}

private:
	template<class Fn>
	void generate(const Fn& fn, std::size_t n_open = 0, std::size_t n_close = 0) const
	{
		if (str_.length() == 2 * n_pairs_)
		{
			fn(str_);
			return;
		}

		if (n_open < n_pairs_)
		{
			str_.push_back(open_);
			generate(fn, n_open + 1, n_close);
			str_.pop_back();
		}

		if (n_close < n_open)
		{
			str_.push_back(close_);
			generate(fn, n_open, n_close + 1);
			str_.pop_back();
		}
	}

private:
	const std::size_t n_pairs_;
	const char open_;
	const char close_;

	mutable std::string str_;
};

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		read(n_pairs_);
	}

	virtual void solve(unsigned int) override
	{
		Parentheses_generator gen(n_pairs_);
		gen([](auto& str) { write_ln(str); });
		write_ln();
	}

private:
	std::size_t n_pairs_;
};

MAIN

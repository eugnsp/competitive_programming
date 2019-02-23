/*********************************************************************
Variable radix Huffman encoding
-------------------------------
UVa ID: 002 40

Huffman encoding is a method of developing an optimal encoding of the
symbols in a source alphabet using symbols from a target alphabet when
the frequencies of each of the symbols in the source alphabet are
known. Optimal means the average length of an encoded message will be
inimized. In this problem you are to determine an encoding of the
first N uppercase letters (the source alphabet, S_1 through S_N), with
frequencies f_1 through f_N) into the first R decimal digits (the
target alphabet, T_1 through T_R).
...

Input
-----
The input will contain one or more data sets, one per line. Each data
set consists of an integer value for R (between 2 and 10), an integer
value for N (between 2 and 26), and the integer frequencies f_1
through f_N, each of which is between 1 and 999. The end of data for
the entire input is the number 0 for R; it is not considered to be a
separate data set.

Output
------
For each data set, display its number (numbering is sequential
starting with 1) and the average target symbol length (rounded to two
decimal places) on one line. Then display the N letters of the source
alphabet and the corresponding Huffman codes, one letter and code per
line. Print a blank line after each test case.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "util.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iomanip>
#include <queue>
#include <vector>
#include <tuple>
#include <utility>

using Freq = unsigned int;

class Huffman_tree
{
private:
	static constexpr std::size_t no_letter = 0;

	struct Node
	{
		std::size_t letter;
		Freq freq;
		std::vector<Node> children;

		bool operator<(const Node& other) const
		{
			return std::tie(other.freq, other.letter) < std::tie(freq, letter);
		}
	};

public:
	Huffman_tree(std::size_t radix, std::vector<Freq> freqs) : radix_(radix)
	{
		assert(radix > 1);
		std::priority_queue<Node> heap;

		const auto n_fict = n_fict_letters(radix, freqs.size());
		for (std::size_t l = 0; l < n_fict; ++l)
			heap.push({no_letter, 0});

		for (std::size_t l = 0; l < freqs.size(); ++l)
			heap.push({l + 1, freqs[l]});

		while (heap.size() >= radix_)
		{
			Node node{no_letter, 0};
			for (std::size_t r = 0; r < radix_; ++r)
			{
				node.children.push_back(heap.top());
				node.freq += node.children.back().freq;

				heap.pop();
			}
			heap.push(node);
		}
		assert(heap.size() == 1);

		auto& root = heap.top();

		codes_.resize(freqs.size());
		double f1 = 0, f2 = 0;

		std::vector<std::size_t> current_code;
		dfs(root, current_code);

		for (std::size_t l = 0; l < freqs.size(); ++l)
		{
			f1 += freqs[l] * codes_[l].size();
			f2 += freqs[l];
		}

		avg_length_ = f1 / f2;
	}

	void dfs(const Node& root, std::vector<std::size_t>& current_code)
	{
		for (std::size_t r = 0; r < root.children.size(); ++r)
		{
			auto& child = root.children[r];
			if (child.letter != no_letter)
			{
				codes_[child.letter - 1] = current_code;
				codes_[child.letter - 1].push_back(r);
			}
			else
			{
				current_code.push_back(r);
				dfs(child, current_code);
				current_code.pop_back();
			}
		}
	}

	double avg_length() const
	{
		return avg_length_;
	}

	const std::vector<std::size_t>& get_code(std::size_t letter) const
	{
		return codes_[letter];
	}

private:
	static std::size_t n_fict_letters(std::size_t radix, std::size_t n_letters)
	{
		assert(radix > 1);
		auto n_total = radix;
		while (n_total < n_letters)
			n_total += radix - 1;
		return n_total - n_letters;
	}

	const std::size_t radix_;
	double avg_length_;
	std::vector<std::vector<std::size_t>> codes_;
};

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		if (!read(radix_) || radix_ == 0)
			return false;

		return read_size_vec(freqs_);
	}

	virtual void solve(unsigned int i_case) override
	{
		Huffman_tree ht(radix_, freqs_);

		if (freqs_.size() == 1)
		{
			write_ln("Set ", i_case + 1, "; average length 0.00");
			write_ln("    A:");
		}
		else
		{
			write_ln(
				"Set ",
				i_case + 1,
				"; average length ",
				std::fixed,
				std::setprecision(2),
				ht.avg_length());

			for (std::size_t l = 0; l < freqs_.size(); ++l)
			{
				auto& code = ht.get_code(l);
				write("    ", to_ucase_letter(l), ": ");
				write_vec(code, [](std::size_t c) { return to_digit(c); }, "");
				write_ln();
			}
		}
		write_ln();
	}

private:
	std::size_t radix_;
	std::vector<Freq> freqs_;
};

MAIN(CP)

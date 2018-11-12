/*********************************************************************
Variable radix Huffman encoding
-------------------------------
UVa ID: 119 97

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
	static constexpr auto fict_letter = static_cast<std::size_t>(-1);

	struct Node
	{
		Node(std::size_t letter = fict_letter, Freq freq = 0,
			std::vector<Node> children = {}) : letter(letter), freq(freq), children(children)
		{ }

		std::size_t letter;
		Freq freq;
		std::vector<Node> children;

		bool operator<(const Node& other) const
		{
			return other.order() < order();
		}

	private:
		std::tuple<Freq, std::size_t, std::size_t> order() const
		{
			// Fictitious letters should precede all other letters
			return {freq, letter + 1, children.size()};
		}
	};

public:
	Huffman_tree(std::size_t radix, std::vector<Freq> freqs)
		: radix_(radix)
	{
		assert(radix >= 1);

		const auto n_letters = freqs.size();
		std::priority_queue<Node> heap;

		const auto n_fict = n_fict_letters(radix, freqs.size());
		for (std::size_t l = 0; l < n_fict; ++l)
			heap.emplace();

		for (std::size_t l = 0; l < n_letters; ++l)
			heap.emplace(l, freqs[l]);

		while (heap.size() >= radix_)
		{
			Node node;
			for (std::size_t r = 0; r < radix_; ++r)
			{
				auto& top = heap.top();
				node.letter = std::min(node.letter, top.letter);
				node.children.push_back(top);
				node.freq += node.children.back().freq;

				heap.pop();
			}
			heap.push(std::move(node));
		}
		assert(heap.size() == 1);

		codes_.resize(n_letters);
		std::vector<std::size_t> current_code;
		dfs_huffman_tree(heap.top(), current_code);

		double total_freq_length = 0;
		double total_freq = 0;
		for (std::size_t l = 0; l < n_letters; ++l)
		{
			total_freq_length += freqs[l] * codes_[l].size();
			total_freq += freqs[l];
		}

		avg_length_ = total_freq_length / total_freq;
	}

	void dfs_huffman_tree(const Node& root, std::vector<std::size_t>& current_code)
	{
		for (std::size_t r = 0; r < root.children.size(); ++r)
		{
			auto& child = root.children[r];
			const auto is_leaf = child.children.empty();

			if (is_leaf)
			{
				if (child.letter != fict_letter)
				{
					codes_[child.letter] = current_code;
					codes_[child.letter].push_back(r);
				}
			}
			else
			{
				current_code.push_back(r);
				dfs_huffman_tree(child, current_code);
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
		assert(n_letters > 1);
		return radix - 2 - ((n_letters - 2) % (radix - 1));
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

		write_ln("Set ", i_case + 1, "; average length ", std::fixed,
			std::setprecision(2), ht.avg_length());

		for (std::size_t l = 0; l < freqs_.size(); ++l)
		{
			auto& code = ht.get_code(l);
			write("    ", to_ucase_letter(l), ": ");
			write_vec(code, [](std::size_t c) { return to_digit(c); }, "");
			write_ln();
		}

		write_ln();
	}

private:
	std::size_t radix_;
	std::vector<Freq> freqs_;
};

MAIN(CP)

/*********************************************************************
Helping Fill Bates
------------------
UVa ID: 105 67

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <string>
#include <vector>
#include <utility>

using Index = unsigned int;

class Helping_Fill_Bates
{
public:
	static const std::pair<Index, Index> no_match;

public:
	Helping_Fill_Bates(const std::string& candidates)
	{
		Index i = 0;
		for (auto c : candidates)
			indices_[get_index(c)].push_back(i++);
	}

	std::pair<Index, Index> find_match(const std::string& query) const
	{
		auto q_ch = query.begin();
		if (indices_[get_index(*q_ch)].empty())
			return no_match;

		const Index first_index = indices_[get_index(*q_ch)].front();
		Index current_index = first_index;

		for (++q_ch; q_ch != query.end(); ++q_ch)
		{
			const auto& indices = indices_[get_index(*q_ch)];
			const auto index = std::upper_bound(indices.begin(), indices.end(), current_index);
			if (index == indices.end())
				return no_match;

			current_index = *index;
		}
		return {first_index, current_index};
	}

private:
	static constexpr auto abc_len = 26U;

	static Index get_index(char c)
	{
		if (c >= 'a' && c <= 'z')
			return c - 'a';
		else
			return c - 'A' + abc_len;
	}

private:
	std::array<std::vector<Index>, 2 * abc_len> indices_;
};

const std::pair<Index, Index> Helping_Fill_Bates::no_match = {static_cast<Index>(-1),
															  static_cast<Index>(-1)};

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		if (!read(candidates_))
			return false;

		return read_size_vec(queries_);
	}

	virtual void solve(unsigned int) override
	{
		const Helping_Fill_Bates helping(candidates_);

		for (auto& q : queries_)
		{
			const auto match = helping.find_match(q);
			if (match != Helping_Fill_Bates::no_match)
				write_ln("Matched ", match.first, ' ', match.second);
			else
				write_ln("Not matched");
		}
	}

private:
	std::string candidates_;
	std::vector<std::string> queries_;
};

MAIN(CP)

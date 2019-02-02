/*********************************************************************
Cyborg genes
------------
UVa ID: 107 23

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cstddef>
#include <string>
#include <vector>
#include <algorithm>
#include <cassert>

class CP : public CP1
{
private:
	struct Scs
	{
		std::size_t length;
		std::size_t count;
	};

private:
	virtual void read_input() override
	{
		read_ln(s1_);
		read_ln(s2_);

		assert(s1_.length() <= 30 && s2_.length() <= 30);
	}

	virtual void solve(unsigned int i_case) override
	{
		/*********************************************************************
		scs(i, j).length is the length of the shortest common supersequence
			(SCS) of the prefixes (s1[0 ... i-1]) and (s2[0 ... j-1]),
		scs(i, j).count is the number of SCS of the prefixes.

		The recurrence relation:
			scs(i, j).length = 1 + scs(i - 1, j - 1).length,
			scs(i, j).count = scs(i - 1, j - 1).count
												if (s1[i - 1] == s2[j - 1]),
			scs(i, j).length = 1 +
						+ min{scs(i - 1, j).length, scs(i, j - 1).length},
												if (s1[i - 1] != s2[j - 1]).
			scs(i, j).count = scs(i - 1, j).count	if min lengths are the same,
			scs(i, j).count = scs(i - 1, j).count + scs(i, j - 1).count
													otherwise.

		The base case:
			scs(i, 0).length = i, scs(i, 0).count = 1	for all (i),
			scs(0, j).length = j, scs(0, j).count = 1	for all (j).
		**********************************************************************/

		const auto len_s1 = s1_.length();
		const auto len_s2 = s2_.length();

		std::vector<Scs> scs_col(len_s1 + 1), scs_prev(len_s1 + 1);
		for (std::size_t i = 0; i <= len_s1; ++i)
		{
			scs_col[i].length = i;
			scs_col[i].count = 1;
		}

		for (std::size_t j = 1; j <= len_s2; ++j)
		{
			std::swap(scs_col, scs_prev);

			scs_col[0].length = j;
			scs_col[0].count = 1;
			for (std::size_t i = 1; i <= len_s1; ++i)
				if (s1_[i - 1] == s2_[j - 1])
				{
					const auto& cs = scs_prev[i - 1];
					scs_col[i].length = 1 + cs.length;
					scs_col[i].count = cs.count;
				}
				else
				{
					const auto& cs1 = scs_col[i - 1];
					const auto& cs2 = scs_prev[i];

					scs_col[i].length = 1 + std::min(cs1.length, cs2.length);
					scs_col[i].count = 0;
					if (scs_col[i].length == cs1.length + 1)
						scs_col[i].count += cs1.count;
					if (scs_col[i].length == cs2.length + 1)
						scs_col[i].count += cs2.count;
				}
		}

		write_ln("Case #", i_case + 1, ": ", scs_col.back().length, ' ', scs_col.back().count);
	}

private:
	std::string s1_;
	std::string s2_;
};

MAIN(CP)

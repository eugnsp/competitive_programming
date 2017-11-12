/*********************************************************************
The jackpot
-----------
UVa ID: 10684

Goal:	identify the maximum possible gain out of a sequence of bets.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_kadane_max_sum.hpp"
#include <cstddef>
#include <iterator>
#include <algorithm>
#include <vector>

class Jackpot : public CP2
{
private:
	using Bet = int;
	
private:
	virtual bool read_input(std::istream& in) override
	{
		// <number of bets = n>
		// <bet_1>
		// ... 
		// <bet_n>

		std::size_t n;
		
		in >> n;
		if (n == 0)
			return false;

		bets_.resize(n);
		std::copy_n(std::istream_iterator<Bet>(in), bets_.size(), bets_.begin());
		
		return true;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		const auto max_gain = kadane_max_sum(bets_.cbegin(), bets_.cend());
		if (max_gain > 0)
			out << "The maximum winning streak is " << max_gain << ".\n";
		else
			out << "Losing streak.\n";
	}

private:
	std::vector<Bet> bets_;
};

int main()
{
	Jackpot p;
	return p.run();
}

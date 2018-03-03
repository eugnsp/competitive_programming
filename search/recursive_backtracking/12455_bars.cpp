/*********************************************************************
Bars
----
UVa ID: 12455

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

// Note: search space is small, and this naive solution
// using backtracking is fast enough

#include "base.hpp"
#include "util.hpp"
#include <cassert>
#include <vector>

using Length = unsigned int;

class Bars
{
public:
	Bars(const std::vector<Length>& lengths, Length length)
		: lengths_(lengths), length_(length)
	{ }

	bool can_be_assembled() const
	{
		return length_ == 0 || can_be_assembled(0, 0);
	}

private:
	bool can_be_assembled(Length length, std::size_t bar) const
	{
		if (length > length_ || bar >= lengths_.size())
			return false;

		const auto new_length = length + lengths_[bar];
		if (new_length == length_)
			return true;

		return can_be_assembled(length, bar + 1) || can_be_assembled(new_length, bar + 1);
	}

private:
	const std::vector<Length>& lengths_;
	const Length length_;
};

class CP : public CP1
{
private:
	virtual void read_input(std::istream& in) override
	{
		std::size_t n_bars;

		in >> length_ >> n_bars;
		assert(length_ <= 1000 && between(n_bars, 1, 20));

		lengths_.resize(n_bars);
		for (auto& l : lengths_)
			in >> l;
	}

	virtual void solve(std::ostream& out, std::size_t) const override
	{
		const Bars bars(lengths_, length_);
		out << (bars.can_be_assembled() ? "YES" : "NO") << '\n';
	}

private:
	Length length_;
	std::vector<Length> lengths_;
};

int main()
{
	CP p;
	return p.run();
}

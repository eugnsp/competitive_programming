// Pebble solitaire
// ----------------
//
// Goal: find the minimum number of pebbles left on the board
// after all possible moves have been made.
//
// UVa ID: 10651
// This file is covered by the LICENSE file in the root of this project.

#include "base.hpp"
#include "bit_mask.hpp"
#include <cstddef>
#include <array>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

class Pebble_solitaire : public Program1
{
private:
	using Number = unsigned int;
	static constexpr auto max_number = static_cast<Number>(-1);

private:
	virtual void read_input() override
	{
		// <pebble_1>...<pebble_12>

		std::generate_n(pebbles_.begin(), pebbles_.size(), []()
		{
			char s;
			std::cin >> s;
			assert(s == 'o' || s == '-');
			return (s == 'o');
		});
	}

	virtual void solve(std::size_t) override
	{
		m_.assign(Bit_mask{pebbles_.size()}.size(), max_number);
		std::cout << min_number(Bit_mask(pebbles_)) << '\n';
	}

	Number min_number(Bit_mask mask)
	{
		if (m_[mask] != max_number)
			return m_[mask];

		const Bit_mask m111(3, 0b111);
		const Bit_mask m011(3, 0b011);
		const Bit_mask m110(3, 0b110);

		bool move_found = false;
		for (std::size_t i = 0; i < pebbles_.size() - 2; ++i)
		{
			auto shifted_mask = (mask >> i);
			shifted_mask.truncate(3);

			if (shifted_mask == m011 || shifted_mask == m110)
			{
				auto move_mask = mask;
				move_mask.xor_at_pos(i, m111);

				m_[mask] = std::min(m_[mask], min_number(move_mask));
				move_found = true;
			}
		}

		if (!move_found)
			m_[mask] = static_cast<Number>(mask.count());

		return m_[mask];
	}

private:
	std::array<bool, 12> pebbles_;
	std::vector<Number> m_;
};

int main()
{
	Pebble_solitaire p;
	return p.run();
}

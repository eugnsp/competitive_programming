/*********************************************************************
Pebble solitaire
----------------
UVa ID: 106 51

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "bit_mask.hpp"
#include <algorithm>
#include <array>
#include <cassert>
#include <cstddef>
#include <vector>

class CP : public CP1
{
private:
	using Number = unsigned int;
	static constexpr auto max_number = static_cast<Number>(-1);
	static constexpr std::size_t n_pebbles = 12;

private:
	virtual void read_input() override
	{
		std::generate_n(pebbles_.begin(), n_pebbles, []() {
			char s;
			read(s);
			assert(s == 'o' || s == '-');
			return (s == 'o');
		});
	}

	virtual void solve(unsigned int) override
	{
		m_.assign(Bit_mask(n_pebbles).size(), +max_number); // rvalue
		write_ln(min_number(Bit_mask(pebbles_)));
	}

	Number min_number(Bit_mask mask)
	{
		auto& m = m_[mask];
		if (m != max_number)
			return m;

		const Bit_mask m111(3, 0b111);
		const Bit_mask m011(3, 0b011);
		const Bit_mask m110(3, 0b110);

		bool move_found = false;
		for (std::size_t i = 0; i < n_pebbles - 2; ++i)
		{
			auto shifted_mask = (mask >> i);
			shifted_mask.truncate(3);

			if (shifted_mask == m011 || shifted_mask == m110)
			{
				auto move_mask = mask;
				move_mask.xor_at_pos(i, m111);

				m = std::min(m, min_number(move_mask));
				move_found = true;
			}
		}

		if (!move_found)
			m = static_cast<std::size_t>(mask.count());

		return m;
	}

private:
	std::array<bool, n_pebbles> pebbles_;
	std::vector<Number> m_;
};

MAIN


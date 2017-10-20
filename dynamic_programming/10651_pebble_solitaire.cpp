// Pebble solitaire
// ----------------
//
// Goal: find the minimum number of pebbles left on the board
// after all possible moves have been made.
//
// UVa ID: 10651
// This file is covered by the LICENSE file in the root of this project.

#include "bit_mask.hpp"
#include <cstddef>
#include <array>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

using Number = unsigned int;
constexpr auto max_number = static_cast<Number>(-1);

template<std::size_t n>
Number min_number_impl(std::vector<Number>& m, Bit_mask mask)
{
	if (m[mask] != max_number)
		return m[mask];

	const Bit_mask m111(3, 0b111);
	const Bit_mask m011(3, 0b011);
	const Bit_mask m110(3, 0b110);

	bool move_found = false;
	for (std::size_t i = 0; i < n - 2; ++i)
	{
		auto shifted_mask = (mask >> i);
		shifted_mask.truncate(3);

		if (shifted_mask == m011 || shifted_mask == m110)
		{
			auto move_mask = mask;
			move_mask.xor_at_pos(i, m111);

			m[mask] = std::min(m[mask], min_number_impl<n>(m, move_mask));
			move_found = true;
		}
	}

	if (!move_found)
		m[mask] = static_cast<Number>(mask.count());

	return m[mask];
}

template<std::size_t n>
Number min_number(const std::array<bool, n>& pebbles)
{
	static_assert(n >= 3, "Too few pebbles");

	std::vector<Number> m(Bit_mask{n}.size(), max_number);
	return min_number_impl<n>(m, Bit_mask(pebbles));
}

// <number of test cases>
// <pebble_1>...<pebble_12>

int main()
{
	std::size_t n_tests;
	std::cin >> n_tests;

	while (n_tests--)
	{
		std::array<bool, 12> pebbles;
		std::generate_n(pebbles.begin(), pebbles.size(), []()
		{
			char s;
			std::cin >> s;
			return (s == 'o');
		});

		std::cout << min_number(pebbles) << '\n';
	}

	return 0;
}
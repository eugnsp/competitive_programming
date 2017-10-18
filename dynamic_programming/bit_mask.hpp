// Bit masks common routines
// -------------------------
//
// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <cstddef>
#include <type_traits>
#include <cassert>

// Returns true if the (i)-th bit in the (mask) is set
template<typename T>
bool is_bit_set(T mask, std::size_t i)
{
	static_assert(std::is_unsigned<T>::value, "Type T should be unsigned");
	assert(i < 8 * sizeof(T));

	const auto ith_bit_mask = static_cast<T>(1) << i;
	return (mask & ith_bit_mask) == ith_bit_mask;
}

// Sets the (i)-th bit in the (mask)
template<typename T>
void set_bit(T& mask, std::size_t i)
{
	static_assert(std::is_unsigned<T>::value, "Type T should be unsigned");
	assert(i < 8 * sizeof(T));

	const auto ith_bit_mask = static_cast<T>(1) << i;
	mask |= ith_bit_mask;
}

// Resets the (i)-th bit in the (mask)
template<typename T>
void reset_bit(T& mask, std::size_t i)
{
	static_assert(std::is_unsigned<T>::value, "Type T should be unsigned");
	assert(i < 8 * sizeof(T));

	const auto ith_bit_mask = static_cast<T>(1) << i;
	mask &= ~ith_bit_mask;
}

// Toggles the (i)-th bit in the (mask)
template<typename T>
void toggle_bit(T& mask, std::size_t i)
{
	static_assert(std::is_unsigned<T>::value, "Type T should be unsigned");
	assert(i < 8 * sizeof(T));

	const auto ith_bit_mask = static_cast<T>(1) << i;
	mask ^= ith_bit_mask;
}

// Toggles the (i)-th bit in the (mask)
template<typename T>
std::size_t n_set_bits(T mask)
{
	static_assert(std::is_unsigned<T>::value, "Type T should be unsigned");
	
	std::size_t n = 0;
	while (mask != 0)
	{ 
		mask &= mask - 1;	// Reset the right-most bit
		++n;
	}

	return n;
}

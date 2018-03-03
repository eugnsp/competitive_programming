// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <type_traits>

#define CHECK_MASK_TYPE(T) static_assert(std::is_unsigned<T>::value, "Mask type should be unsigned")

////////////////////////////////////////////////////////////
// Constant patterns

template<typename T>
T all_bits()
{
	CHECK_MASK_TYPE(T);
	return static_cast<T>(-1);
}

template<typename T, typename N>
T nth_bit(N n)
{
	CHECK_MASK_TYPE(T);
	return static_cast<T>(1) << n;
}

template<typename T, typename N>
T n_ls_bits(N n)
{
	if (n == 8 * sizeof(T))
		return all_bits<T>();
	else
		return nth_bit<T>(n) - static_cast<T>(1);
}

////////////////////////////////////////////////////////////
// Bit set/reset

template<typename T, typename N>
bool is_bit_set(T mask, N n)
{
	return mask & nth_bit<T>(n);
}

template<typename T, typename N>
void set_bit(T& mask, N n, bool bit = true)
{
	if (bit)
		mask |= nth_bit<T>(n);
}

template<typename T, typename N>
void reset_bit(T& mask, N n)
{
	mask &= ~nth_bit<T>(n);
}

// Resets all but (n) LSBs in the (mask)
template<typename T, typename N>
void keep_ls_bits(T& mask, N n)
{
	mask &= n_ls_bits<T>(n);
}

// Resets the LSB that is set
template<typename T>
void reset_ls_set_bit(T& mask)
{
	CHECK_MASK_TYPE(T);
	mask &= mask - static_cast<T>(1);
}

#ifdef __GNUG__

unsigned int ls_set_bit_pos(unsigned int mask)
{
	return static_cast<unsigned int>(__builtin_ctz(mask));
}

unsigned int ls_set_bit_pos(unsigned long mask)
{
	return static_cast<unsigned int>(__builtin_ctzl(mask));
}

unsigned int ls_set_bit_pos(unsigned long long mask)
{
	return static_cast<unsigned int>(__builtin_ctzll(mask));
}

#else

template<typename T>
unsigned int ls_set_bit_pos(T mask)
{
	CHECK_MASK_TYPE(T);
	unsigned int n = 0;
	while (!(mask & static_cast<T>(1)) && n < 8 * sizeof(T))
	{
		mask >>= 1;
		++n;
	}
	return n;
}

#endif

template<typename T, typename N>
T with_bit_set(T mask, N n, bool bit = true)
{
	set_bit(mask, n, bit);
	return mask;
}

template<typename T, typename N>
T with_bit_reset(T mask, N n)
{
	reset_bit(mask, n);
	return mask;
}

template<typename T>
T ls_set_bit(T mask)
{
	CHECK_MASK_TYPE(T);
	return mask & (~mask + static_cast<T>(1));
}

////////////////////////////////////////////////////////////
// Bit flip

template<typename T, typename N>
void flip_bit(T& mask, N n)
{
	mask ^= ~nth_bit<T>(n);
}

template<typename T, typename N>
void flip_n_ls_bits(T& mask, N n)
{
	mask ^= n_ls_bits<T>(n);
}

template<typename T, typename N>
T with_bit_flipped(T mask, N n)
{
	flip_bit(mask, n);
	return mask;
}

////////////////////////////////////////////////////////////
// Bit counting

#ifdef __GNUG__

unsigned int count_bits(unsigned int mask)
{
	return static_cast<unsigned int>(__builtin_popcount(mask));
}

unsigned int count_bits(unsigned long mask)
{
	return static_cast<unsigned int>(__builtin_popcountl(mask));
}

unsigned int count_bits(unsigned long long mask)
{
	return static_cast<unsigned int>(__builtin_popcountll(mask));
}

#else

template<typename T>
unsigned int count_bits(T mask)
{
	unsigned int n = 0;
	while (mask != 0)
	{
		reset_rm_bit(mask);
		++n;
	}
	return n;
}

#endif

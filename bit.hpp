#pragma once
#include <cassert>
#include <string>
#include <type_traits>

#define CHECK_UNSIGNED_TYPE(T) static_assert(std::is_unsigned<T>::value, "Type should be unsigned")

////////////////////////////////////////////////////////////
// Constant patterns

template<typename T>
constexpr T all_bits()
{
	CHECK_UNSIGNED_TYPE(T);
	return static_cast<T>(-1);
}

template<typename T, typename N>
constexpr T nth_bit(N n)
{
	CHECK_UNSIGNED_TYPE(T);
	return static_cast<T>(1) << n;
}

template<typename T, typename N>
T n_ls_bits(N n)
{
	return (n == 0) ? 0 : all_bits<T>() >> (8 * sizeof(T) - n);
}

////////////////////////////////////////////////////////////
// Bit set/reset

template<typename T, typename N>
bool is_bit_set(T mask, N n)
{
	return mask & nth_bit<T>(n);
}

template<unsigned int n, typename T>
bool is_bit_set(T mask)
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
	CHECK_UNSIGNED_TYPE(T);
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

unsigned int ms_set_bit_pos(unsigned int mask)
{
	return static_cast<unsigned int>(8 * sizeof(unsigned int) - __builtin_clz(mask));
}

unsigned int ms_set_bit_pos(unsigned long mask)
{
	return static_cast<unsigned int>(8 * sizeof(unsigned long) - __builtin_clzl(mask));
}

unsigned int ms_set_bit_pos(unsigned long long mask)
{
	return static_cast<unsigned int>(8 * sizeof(unsigned long long) - __builtin_clzll(mask));
}

#else

template<typename T>
unsigned int ls_set_bit_pos(T mask)
{
	CHECK_UNSIGNED_TYPE(T);
	unsigned int n = 0;
	while (!(mask & static_cast<T>(1)) && n < 8 * sizeof(T))
	{
		mask >>= 1;
		++n;
	}
	return n;
}

template<typename T>
unsigned int ms_set_bit_pos(T mask)
{
	CHECK_UNSIGNED_TYPE(T);
	unsigned int n = 0;
	while (mask != 0)
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

// Returns mask in which only the least significant set bit of (mask) is set
template<typename T>
T ls_set_bit(T mask)
{
	CHECK_UNSIGNED_TYPE(T);
	return mask & (~mask + static_cast<T>(1));
}

////////////////////////////////////////////////////////////
// Bit flip

template<typename T, typename N>
void flip_bit(T& mask, N n)
{
	mask ^= nth_bit<T>(n);
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
	while (mask)
	{
		reset_ls_set_bit(mask);
		++n;
	}
	return n;
}

#endif

//////////////////////////////////////////////////////////////////////////
// String representations of masks

template<typename T>
T string_to_mask(const std::string& mask)
{
	CHECK_UNSIGNED_TYPE(T);
	assert(mask.length() <= 8 * sizeof(T));
	return static_cast<T>(std::stoul(mask, 0, 2));
}

//////////////////////////////////////////////////////////////////////////
// Logarithms and powers

template<typename T>
unsigned int floor_log2(T x)
{
	assert(x != 0);
	return ms_set_bit_pos(x) - 1;
}

template<typename T>
unsigned int ceil_log2(T x)
{
	assert(x != 0);
	if (x == 1)
		return 0;
	else
		return ms_set_bit_pos(x - 1);
}

template<typename T>
bool is_pow2(T x)
{
	CHECK_UNSIGNED_TYPE(T);
	return !(x & (x - 1));
}

// Returns 2^n
template<typename T>
T pow2(unsigned int n)
{
	return static_cast<T>(1) << n;
}

template<typename T>
T prev_pow2(T x)
{
	CHECK_UNSIGNED_TYPE(T);
	if (x == 0)
		return x;
	else
		return pow2<T>(floor_log2(x));
}

template<typename T>
T next_pow2(T x)
{
	if (is_pow2(x))
		return x;
	return pow2<T>(floor_log2(x) + 1);
}
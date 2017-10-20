// Bit masks general routines
// --------------------------
//
// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <cstddef>
#include <array>
#include <vector>
#include <cassert>

class Bit_mask
{ 
public:
	Bit_mask(std::size_t length, std::size_t mask)
		: mask_(mask), length_(length)
	{
		assert(length < 8 * sizeof(std::size_t));
	}

	explicit Bit_mask(std::size_t length)
		: Bit_mask(length, 0)
	{ }

	explicit Bit_mask(const std::vector<bool>& mask)
		: Bit_mask(mask.size())
	{
		std::size_t nth_bit = 1;
	 	for (auto f : mask)
	 	{
	 		if (f)
		 		mask_ |= nth_bit;
			nth_bit <<= 1;
		}
	}

	template<std::size_t n>
	explicit Bit_mask(const std::array<bool, n>& mask)
		: Bit_mask(mask.size())
	{
		std::size_t nth_bit = 1;
		for (auto f : mask)
		{
			if (f)
				mask_ |= nth_bit;
			nth_bit <<= 1;
		}
	}

	Bit_mask(const Bit_mask& other)
		: Bit_mask(other.length_, other.mask_)
	{ }

	Bit_mask& operator=(const Bit_mask& other)
	{ 
		assert(length_ == other.length_);
		mask_ = other.mask_;
		return *this;
	};

	operator std::size_t() const
	{
		return mask_;
	}

	bool operator[](std::size_t i) const
	{
		assert(i < length_);
		return mask_ & ith_bit(i);
	}

	Bit_mask& set(std::size_t i)
	{
		assert(i < length_);
		mask_ |= ith_bit(i);
		return *this;
	}

	Bit_mask& set()
	{ 
		mask_ = all_bits(length_);
		return *this;
	}

	Bit_mask& reset(std::size_t i)
	{
		assert(i < length_);
		mask_ &= ~ith_bit(i);
		return *this;
	}

	Bit_mask& reset()
	{
		mask_ = 0;
		return *this;
	}

	Bit_mask& flip(std::size_t i)
	{
		assert(i < length_);
		mask_ ^= ith_bit(i);
		return *this;
	}

	Bit_mask& flip()
	{
		mask_ ^= all_bits(length_);
		return *this;
	}

#ifdef __GNUG__
	std::size_t count() const
	{
		return count_impl(mask_);
	}
#else
	std::size_t count() const
	{
		std::size_t n = 0;
		auto mask = mask_;
		while (mask != 0)
		{
			mask &= mask - 1;	// Reset the right-most bit
			++n;
		}
		return n;
	}
#endif

	Bit_mask& xor_at_pos(std::size_t pos, const Bit_mask& other)
	{
		assert(pos + other.length_ <= length_);
		mask_ ^= (other.mask_ << pos);
		return *this;
	}

	void truncate(std::size_t new_length)
	{
		length_ = new_length;
		mask_ &= all_bits(new_length);
	}

	std::size_t size() const
	{
		return static_cast<std::size_t>(1) << length_;
	}

	Bit_mask operator<<(std::size_t shift) const
	{
		auto tmp(*this);
		tmp.mask_ <<= shift;
		return tmp;
	}

	Bit_mask& operator<<=(std::size_t shift)
	{
		mask_ <<= shift;
		return *this;
	}

	Bit_mask operator>>(std::size_t shift) const
	{
		auto tmp(*this);
		tmp.mask_ >>= shift;
		return tmp;
	}

	Bit_mask& operator>>=(std::size_t shift)
	{
		mask_ >>= shift;
		return *this;
	}

	Bit_mask operator&(const Bit_mask& other) const
	{
		auto tmp(*this);
		tmp.mask_ &= other.mask_;
		return tmp;
	}

	Bit_mask operator|(const Bit_mask& other) const
	{
		auto tmp(*this);
		tmp.mask_ |= other.mask_;
		return tmp;
	}

	Bit_mask operator^(const Bit_mask& other) const
	{
		auto tmp(*this);
		tmp.mask_ ^= other.mask_;
		return tmp;
	}

	Bit_mask& operator++()
	{
		++mask_;
		return *this;
	}

	Bit_mask& operator--()
	{
		--mask_;
		return *this;
	}

	bool operator==(const Bit_mask& other) const
	{ 
		assert(length_ == other.length_);
		return mask_ == other.mask_;
	}

	bool operator!=(const Bit_mask& other) const
	{
		return !(*this == other);
	}

	bool operator<(const Bit_mask& other) const
	{
		assert(length_ == other.length_);
		return mask_ < other.mask_;
	}

	bool operator<=(const Bit_mask& other) const
	{
		assert(length_ == other.length_);
		return mask_ <= other.mask_;
	}

private:
	static std::size_t ith_bit(std::size_t i)
	{ 
		return static_cast<std::size_t>(1) << i;
	}

	static std::size_t all_bits(std::size_t length)
	{
		if (length == 8 * sizeof(std::size_t))
			return static_cast<std::size_t>(-1);
		else
			return ith_bit(length) - 1;
	}

#ifdef __GNUG__
	std::size_t count_impl(unsigned int mask) const
	{
		return static_cast<std::size_t>(__builtin_popcount(mask));
	}

	std::size_t count_impl(unsigned long mask) const
	{
		return static_cast<std::size_t>(__builtin_popcountl(mask));
	}

	std::size_t count_impl(unsigned long long mask) const
	{
		return static_cast<std::size_t>(__builtin_popcountll(mask));
	}
#endif

private:
	std::size_t mask_;
	std::size_t length_;
};

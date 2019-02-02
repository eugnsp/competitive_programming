// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <cstddef>
#include <string>
#include <type_traits>
#include <cassert>

class Bit_mask
{
public:
	using Mask = unsigned long;
	using Length = std::size_t;

public:
	explicit Bit_mask(std::size_t length, Mask mask = 0ul) : mask_(mask), length_(length)
	{
		assert(length <= 8 * sizeof(Mask));
		mask_visualization();
	}

	template<
		class Container,
		typename = typename std::enable_if<
			std::is_same<typename Container::value_type, bool>::value>::type>
	explicit Bit_mask(const Container& mask) : Bit_mask(mask.size())
	{
		Mask nth_bit = 1ul;
		for (auto f : mask)
		{
			if (f)
				mask_ |= nth_bit;
			nth_bit <<= 1;
		}
		mask_visualization();
	}

	explicit Bit_mask(const std::string& mask) : Bit_mask(mask.length(), std::stoul(mask, 0, 2))
	{}

	Bit_mask(const Bit_mask& other) : Bit_mask(other.length_, other.mask_)
	{}

	Bit_mask& operator=(const Bit_mask& other)
	{
		assert(length_ == other.length_);
		mask_ = other.mask_;
		mask_visualization();
		return *this;
	};

	operator Mask() const
	{
		return mask_;
	}

	bool operator[](Length i) const
	{
		assert(i < length_);
		return mask_ & ith_bit(i);
	}

	bool all() const
	{
		return mask_ == all_bits(length_);
	}

	bool any() const
	{
		return mask_ != 0;
	}

	bool none() const
	{
		return !any();
	}

	Bit_mask& set(Length i)
	{
		assert(i < length_);
		mask_ |= ith_bit(i);
		mask_visualization();
		return *this;
	}

	Bit_mask& set()
	{
		mask_ = all_bits(length_);
		mask_visualization();
		return *this;
	}

	Bit_mask& reset(Length i)
	{
		assert(i < length_);
		mask_ &= ~ith_bit(i);
		mask_visualization();
		return *this;
	}

	Bit_mask& reset()
	{
		mask_ = 0;
		mask_visualization();
		return *this;
	}

	Bit_mask& flip(Length i)
	{
		assert(i < length_);
		mask_ ^= ith_bit(i);
		mask_visualization();
		return *this;
	}

	Bit_mask& flip()
	{
		mask_ ^= all_bits(length_);
		mask_visualization();
		return *this;
	}

	Bit_mask with_set(Length i) const
	{
		assert(i < length_);
		auto tmp(*this);
		tmp.mask_ |= ith_bit(i);
		return tmp;
	}

	Bit_mask with_reset(Length i) const
	{
		assert(i < length_);
		auto tmp(*this);
		tmp.mask_ &= ~ith_bit(i);
		return tmp;
	}

	Bit_mask with_flipped(Length i) const
	{
		assert(i < length_);
		auto tmp(*this);
		tmp.mask_ ^= ith_bit(i);
		return tmp;
	}

#ifdef __GNUG__
	Length count() const
	{
		return static_cast<Length>(__builtin_popcountl(mask_));
	}
#else
	Length count() const
	{
		Length n = 0;
		auto mask = mask_;
		while (mask != 0)
		{
			mask &= mask - 1; // Reset the right-most bit
			++n;
		}
		return n;
	}
#endif

	Bit_mask& xor_at_pos(Length pos, const Bit_mask& other)
	{
		assert(pos + other.length_ <= length_);
		mask_ ^= (other.mask_ << pos);
		mask_visualization();
		return *this;
	}

	void truncate(Length new_length)
	{
		length_ = new_length;
		mask_ &= all_bits(new_length);
		mask_visualization();
	}

	Length length() const
	{
		return length_;
	}

	Mask size() const
	{
		return 1ul << length_;
	}

	std::string to_string() const
	{
		std::string s(length_, '0');
		for (Length i = 0; i < length_; ++i)
			if ((*this)[i])
				s[length_ - i - 1] = '1';

		return s;
	}

	Bit_mask operator<<(Length shift) const
	{
		auto tmp(*this);
		tmp.mask_ <<= shift;
		return tmp;
	}

	Bit_mask& operator<<=(Length shift)
	{
		mask_ <<= shift;
		mask_visualization();
		return *this;
	}

	Bit_mask operator>>(Length shift) const
	{
		auto tmp(*this);
		tmp.mask_ >>= shift;
		return tmp;
	}

	Bit_mask& operator>>=(Length shift)
	{
		mask_ >>= shift;
		mask_visualization();
		return *this;
	}

	Bit_mask operator&(const Bit_mask& other) const
	{
		assert(length_ == other.length_);
		auto tmp(*this);
		tmp.mask_ &= other.mask_;
		return tmp;
	}

	Bit_mask operator|(const Bit_mask& other) const
	{
		assert(length_ == other.length_);
		auto tmp(*this);
		tmp.mask_ |= other.mask_;
		return tmp;
	}

	Bit_mask operator^(const Bit_mask& other) const
	{
		assert(length_ == other.length_);
		auto tmp(*this);
		tmp.mask_ ^= other.mask_;
		return tmp;
	}

	Bit_mask& operator++()
	{
		++mask_;
		mask_visualization();
		return *this;
	}

	Bit_mask& operator--()
	{
		--mask_;
		mask_visualization();
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
	static Mask ith_bit(Length i)
	{
		return 1ul << i;
	}

	static Mask all_bits(Length length)
	{
		if (length == 8 * sizeof(Mask))
			return static_cast<Mask>(-1);
		else
			return ith_bit(length) - 1ul;
	}

	void mask_visualization()
	{
#ifdef _DEBUG
		mask_str_[length_] = 0;
		for (Length i = 0; i < length_; ++i)
			mask_str_[length_ - i - 1] = (*this)[i] ? '1' : '0';
#endif
	}

private:
	Mask mask_ = 0;
	Length length_ = 0;

#ifdef _DEBUG
	char mask_str_[8 * sizeof(Mask) + 1];
#endif
};

// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <cassert>
#include <cstdint>
#include <type_traits>

template<unsigned int size>
class Static_bit_mask
{
	static_assert(size <= 64, "Size is too big");

private:
	using Mask = typename std::conditional<(size > 32), std::uint64_t, std::uint32_t>::type;
	using Size = unsigned int;

public:
	explicit Static_bit_mask(Mask mask = 0U) : mask_(mask)
	{
		mask_visualization();
	}

	bool operator[](Size i) const
	{
		assert(i < size);
		return mask_ & ith_bit(i);
	}

	bool all() const
	{
		return mask_ == all_bits();
	}

	bool any() const
	{
		return mask_ != 0;
	}

	bool none() const
	{
		return !any();
	}

	Static_bit_mask& set(Size i)
	{
		assert(i < size);
		mask_ |= ith_bit(i);
		mask_visualization();
		return *this;
	}

	Static_bit_mask& set()
	{
		mask_ = all_bits();
		mask_visualization();
		return *this;
	}

	Static_bit_mask& reset(Size i)
	{
		assert(i < size);
		mask_ &= ~ith_bit(i);
		mask_visualization();
		return *this;
	}

	Static_bit_mask& reset()
	{
		mask_ = 0;
		mask_visualization();
		return *this;
	}

	Static_bit_mask& flip(Size i)
	{
		assert(i < size);
		mask_ ^= ith_bit(i);
		mask_visualization();
		return *this;
	}

	Static_bit_mask& flip()
	{
		mask_ ^= all_bits();
		mask_visualization();
		return *this;
	}

	Static_bit_mask with_set(Size i) const
	{
		assert(i < size);
		auto tmp(*this);
		tmp.mask_ |= ith_bit(i);
		return tmp;
	}

	Static_bit_mask with_reset(Size i) const
	{
		assert(i < size);
		auto tmp(*this);
		tmp.mask_ &= ~ith_bit(i);
		return tmp;
	}

	Static_bit_mask with_flipped(Size i) const
	{
		assert(i < size);
		auto tmp(*this);
		tmp.mask_ ^= ith_bit(i);
		return tmp;
	}

#ifdef __GNUG__
	Size count() const
	{
		return static_cast<Size>(__builtin_popcountll(mask_));
	}
#else
	Size count() const
	{
		Size n = 0;
		auto mask = mask_;
		while (mask != 0)
		{
			mask &= mask - 1; // Reset the right-most bit
			++n;
		}
		return n;
	}
#endif

	Static_bit_mask operator<<(Size shift) const
	{
		auto tmp(*this);
		tmp.mask_ <<= shift;
		return tmp;
	}

	Static_bit_mask& operator<<=(Size shift)
	{
		mask_ <<= shift;
		mask_visualization();
		return *this;
	}

	Static_bit_mask operator>>(Size shift) const
	{
		auto tmp(*this);
		tmp.mask_ >>= shift;
		return tmp;
	}

	Static_bit_mask& operator>>=(Size shift)
	{
		mask_ >>= shift;
		mask_visualization();
		return *this;
	}

	Static_bit_mask& operator++()
	{
		++mask_;
		mask_visualization();
		return *this;
	}

	Static_bit_mask& operator--()
	{
		--mask_;
		mask_visualization();
		return *this;
	}

private:
	static constexpr Mask ith_bit(Size i)
	{
		return static_cast<Mask>(1) << i;
	}

	static constexpr Mask all_bits()
	{
		return (size == 8 * sizeof(Mask)) ? static_cast<Mask>(-1)
										  : ith_bit(size) - static_cast<Mask>(1);
	}

	void mask_visualization()
	{
#ifdef _DEBUG
		mask_str_[size] = 0;
		for (Size i = 0; i < size; ++i)
			mask_str_[size - i - 1] = (*this)[i] ? '1' : '0';
#endif
	}

private:
	Mask mask_ = 0;
#ifdef _DEBUG
	char mask_str_[65];
#endif
};

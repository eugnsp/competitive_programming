// Simple big unsigned integer class
// ---------------------------------
//
// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <cstddef>
#include <vector>
#include <algorithm>
#include <ostream>
#include <cassert>

class Big_uint
{
public:
	explicit Big_uint(unsigned long long = 0);
	static Big_uint minus_inf();

	unsigned char operator[](std::size_t) const;

	Big_uint& operator=(unsigned long long);
	
	Big_uint& operator+=(unsigned long long);

	bool is_zero() const;
	bool is_finite() const;
	bool is_minus_inf() const;
	
	friend bool operator==(const Big_uint&, const Big_uint&);

	std::size_t size() const;

	Big_uint& mul_10();
	friend Big_uint mul_10(const Big_uint&);

private:
	void append(unsigned long long, bool append_if_zero);

private:
	std::vector<unsigned char> data_;
};

//////////////////////////////////////////////////////////////////////////

inline Big_uint::Big_uint(unsigned long long u)
{
	*this = u;
}

inline Big_uint Big_uint::minus_inf()
{
	Big_uint r;
	r.data_.assign({'M'});
	return r;
}

inline unsigned char Big_uint::operator[](std::size_t i) const
{
	assert(is_finite());
	return data_[i];
}

inline Big_uint& Big_uint::operator=(unsigned long long u)
{
	data_.clear();
	append(u, true);
	return *this;
}

inline Big_uint& Big_uint::operator+=(unsigned long long u)
{
	assert(is_finite());
	
	auto carry = u;
	for (auto& d : data_)
	{
		d += carry % 10;
		carry /= 10;
		carry += d / 10;
		d %= 10;
		if (carry == 0)
			break;
	}
	append(carry, false);

	return *this;
}

inline bool Big_uint::is_zero() const
{
	return data_.size() == 1 && data_.front() == 0;
}

inline bool Big_uint::is_finite() const
{
	return !is_minus_inf();
}

inline bool Big_uint::is_minus_inf() const
{
	return data_.size() == 1 && data_.front() == 'M';
}

inline std::size_t Big_uint::size() const
{
	assert(is_finite());
	return data_.size();
}

inline Big_uint& Big_uint::mul_10()
{
	assert(is_finite());
	if (!is_zero())
		data_.insert(data_.begin(), 0);

	return *this;
}

inline void Big_uint::append(unsigned long long u, bool append_if_zero)
{
	if (!append_if_zero && u == 0)
		return;

	do
	{
		data_.push_back(u % 10);
		u /= 10;
	} while (u > 0);
}

/************************************************************************/

inline bool operator<(const Big_uint& u1, const Big_uint& u2)
{
	if (u2.is_minus_inf())
		return false;

	if (u1.is_minus_inf())
		return true;

	if (u1.size() != u2.size())
		return u1.size() < u2.size();

	for (std::size_t i = u1.size() - 1; i != static_cast<std::size_t>(-1); --i)
		if (u1[i] != u2[i])
			return (u1[i] < u2[i]);

	return false;
}

inline bool operator>(const Big_uint& u1, const Big_uint& u2)
{
	return u2 < u1;
}

inline bool operator==(const Big_uint& u1, const Big_uint& u2)
{
	return u1.data_ == u2.data_;
}

inline bool operator!=(const Big_uint& u1, const Big_uint& u2)
{
	return !(u1 == u2);
}

inline bool operator<=(const Big_uint& u1, const Big_uint& u2)
{
	return !(u1 > u2);
}

inline bool operator>=(const Big_uint& u1, const Big_uint& u2)
{
	return !(u1 < u2);
}

inline Big_uint operator+(Big_uint u1, unsigned long long u2)
{
	u1 += u2;
	return u1;
}

inline Big_uint operator+(unsigned long long u1, Big_uint u2)
{
	return u2 + u1;
}

inline std::ostream& operator<<(std::ostream& out, const Big_uint& u)
{
	if (u.is_minus_inf())
		out << "-INF";
	else
		for (std::size_t i = u.size() - 1; i != static_cast<std::size_t>(-1); --i)
			out << static_cast<char>('0' + u[i]);

	return out;
}

inline Big_uint mul_10(const Big_uint& u)
{
	assert(u.is_finite());

	Big_uint r(0);
	if (!u.is_zero())
	{
		r.data_.resize(u.size() + 1);
		std::copy(u.data_.begin(), u.data_.end(), r.data_.begin() + 1);
	}

	return r;
}

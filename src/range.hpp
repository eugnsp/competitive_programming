// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <iosfwd>

// Half-open range [begin, end)
template<typename T>
struct Range
{
	T begin;
	T end;
};

template<typename T>
T mid(const Range<T>& range)
{
	return (range.begin + range.end) / 2;
}

template<typename T>
Range<T> left_half(const Range<T>& range)
{
	return {range.begin, mid(range)};
}

template<typename T>
Range<T> right_half(const Range<T>& range)
{
	return {mid(range), range.end};
}

template<typename T>
T size(const Range<T>& range)
{
	return range.end - range.begin;
}

template<typename T>
bool is_empty(const Range<T>& range)
{
	return range.begin == range.end;
}

// Returns true if the intersection of (range1) and (range2) is not empty
template<typename T>
bool intersects(const Range<T>& range1, const Range<T>& range2)
{
	if (is_empty(range1) || is_empty(range2))
		return false;
		
	return range1.begin < range2.end && range2.begin < range1.end;
}

// Returns true if (range1) includes (range2), returns true if (range2) is empty
template<typename T>
bool includes(const Range<T>& range1, const Range<T>& range2)
{
	return (is_empty(range2) ||
		   (range2.begin <= range1.begin && range1.end <= range2.end));
}

template<typename T>
std::istream& operator>>(std::istream& in, Range<T>& range)
{
	in >> range.begin >> range.end;
	return in;
}

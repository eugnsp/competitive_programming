// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include <cassert>

// Half-open segment [begin, end)
template<typename T>
struct Segment
{
	T begin;
	T end;
};

template<typename T>
T mid(const Segment<T>& segment)
{
	return (segment.begin + segment.end) / 2;
}

template<typename T>
Segment<T> left_half(const Segment<T>& segment)
{
	return {segment.begin, mid(segment)};
}

template<typename T>
Segment<T> right_half(const Segment<T>& segment)
{
	return {mid(segment), segment.end};
}

template<typename T>
T size(const Segment<T>& segment)
{
	return segment.end - segment.begin;
}

template<typename T>
bool is_empty(const Segment<T>& segment)
{
	return segment.begin == segment.end;
}

// Returns true if the intersection of (seg1) and (seg2) is not empty
template<typename T>
bool intersects(const Segment<T>& seg1, const Segment<T>& seg2)
{
	if (is_empty(seg1) || is_empty(seg2))
		return false;
	return seg1.begin < seg2.end && seg2.begin < seg1.end;
}

// Returns true if (seg1) includes (seg2), returns true if (seg2) is empty
template<typename T>
bool includes(const Segment<T>& seg1, const Segment<T>& seg2)
{
	if (is_empty(seg2))
		return true;
	return seg2.begin <= seg1.begin && seg1.end <= seg2.end;
}

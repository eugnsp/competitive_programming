// Point class and basic routines
// ------------------------------
//
// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include "util.hpp"
#include <cmath>

template<typename T>
struct Point
{
	T x;
	T y;

	Point() = default;

	Point(T px, T py)
		: x(px), y(py)
	{  }

	Point& operator-=(const Point& p)
	{
		x -= p.x;
		y -= p.y;
		return *this;
	}

	Point& operator/=(T v)
	{
		x /= v;
		y /= v;
		return *this;
	}
};

template<typename T>
bool operator==(const Point<T>& p1, const Point<T>& p2)
{
	return p1.x == p2.x && p1.y == p2.y;
}

template<typename T>
bool operator!=(const Point<T>& p1, const Point<T>& p2)
{
	return !(p1 == p2);
}

template<typename T>
bool operator<(const Point<T>& p1, const Point<T>& p2)
{
	if (p1.y == p2.y)
		return p1.y < p2.y;
	return p1.x < p2.x;
}

template<typename T>
Point<T> operator-(Point<T> p1, const Point<T>& p2)
{
	return (p1 -= p2);
}

template<typename T>
T dot(const Point<T>& p1, const Point<T>& p2)
{
	return p1.x * p2.x + p1.y * p2.y;
}

template<typename T>
T length_sq(const Point<T>& p)
{
	return dot(p, p);
}

template<typename T>
double distance(const Point<T>& p1, const Point<T>& p2)
{
	auto dv = p1 - p2;
	return std::sqrt(length_sq(dv));
}

template<typename T>
T cross(const Point<T>& p1, const Point<T>& p2)
{
	return p1.x * p2.y - p1.y * p2.x;
}

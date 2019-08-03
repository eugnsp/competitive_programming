// This file is covered by the LICENSE file in the root of this project.

#pragma once
#include "io.hpp"
#include <cmath>

template<typename T>
struct Point
{
	using Type = T;

	T x;
	T y;

	Point() = default;

	Point(T px, T py) : x(px), y(py)
	{}

	Point& operator+=(const Point& point)
	{
		x += point.x;
		y += point.y;
		return *this;
	}

	Point& operator-=(const Point& point)
	{
		x -= point.x;
		y -= point.y;
		return *this;
	}

	Point& operator*=(T scalar)
	{
		x *= scalar;
		y *= scalar;
		return *this;
	}

	Point& operator/=(T scalar)
	{
		x /= scalar;
		y /= scalar;
		return *this;
	}
};

template<typename T>
bool operator==(const Point<T>& point1, const Point<T>& point2)
{
	return point1.x == point2.x && point1.y == point2.y;
}

template<typename T>
bool operator!=(const Point<T>& point1, const Point<T>& point2)
{
	return !(point1 == point2);
}

template<typename T>
bool less_xy(const Point<T>& point1, const Point<T>& point2)
{
	if (point1.x == point2.x)
		return point1.y < point2.y;
	return point1.x < point2.x;
}

template<typename T>
bool less_yx(const Point<T>& point1, const Point<T>& point2)
{
	if (point1.y == point2.y)
		return point1.x < point2.x;
	return point1.y < point2.y;
}

template<typename T>
bool operator<(const Point<T>& point1, const Point<T>& point2)
{
	return less_yx(point1, point2);
}

template<typename T>
Point<T> operator+(Point<T> point1, const Point<T>& point2)
{
	return (point1 += point2);
}

template<typename T>
Point<T> operator-(Point<T> point1, const Point<T>& point2)
{
	return (point1 -= point2);
}

template<typename T>
Point<T> operator/(Point<T> point, T scalar)
{
	return (point /= scalar);
}

template<typename T>
Point<T> operator*(T scalar, Point<T> point)
{
	return (point *= scalar);
}

template<typename T>
Point<T> operator*(Point<T> point, T scalar)
{
	return scalar * point;
}

template<typename T>
T dot(const Point<T>& point1, const Point<T>& point2)
{
	return point1.x * point2.x + point1.y * point2.y;
}

template<typename T>
T cross(const Point<T>& point1, const Point<T>& point2)
{
	return point1.x * point2.y - point1.y * point2.x;
}

template<typename T>
T norm_sq(const Point<T>& point)
{
	return dot(point, point);
}

template<typename T>
T norm(const Point<T>& point)
{
	return std::sqrt(dot(point, point));
}

template<typename T>
double distance_sq(const Point<T>& point1, const Point<T>& point2)
{
	auto dv = point1 - point2;
	return norm_sq(dv);
}

template<typename T>
double distance(const Point<T>& point1, const Point<T>& point2)
{
	return std::sqrt(distance_sq(point1, point2));
}

template<typename T>
bool read(Point<T>& point)
{
	return read(point.x, point.y);
}

template<typename T>
void write(const Point<T>& point)
{
	return write('(', point.x, ',', point.y, ')');
}

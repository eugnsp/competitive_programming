/*********************************************************************
Generate random numbers
-----------------------
UVa ID: 116 34

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <utility>

using T = unsigned int;

// Returns the point in the cycle part of the orbit
// of the transformation (f) starting at the point (x)
// at which the slow pointer meets the fast one
template<class Func>
T collision_point(T x, Func f)
{
	auto slow = x;
	auto fast = f(x);

	while (fast != slow)
	{
		slow = f(slow);
		fast = f(f(fast));
	}

	return slow;
}

// Returns the distance from the point (x) to the point (y)
template<class Func>
T distance(T x, T y, Func f)
{
	T n = 0;
	while (x != y)
	{
		x = f(x);
		++n;
	}
	return n;
}

// Returns the cycle size and the handle size of the orbit
// of the transformation (f) that starts at the point (x)
template<class Func>
std::pair<T, T> handle_and_cycle_sizes(T x, Func f)
{
	T cycle_size = 1;
	T handle_size = 0;

	const auto p = collision_point(x, f);

	auto p1 = f(p);
	while (p != p1)
	{
		p1 = f(p1);
		++cycle_size;
	}
	
	p1 = f(p);
	while (x != p1)
	{
		x = f(x);
		p1 = f(p1);
		++handle_size;
	}

	return {handle_size, cycle_size};
}

class Neumann_generator
{
public:
	T operator()(T x) const
	{
		return from_four_middle_digits(x * x);
	}

private:
	static T from_four_middle_digits(T n)
	{
		return (n / 1'00) % 1'00'00;
	}
};

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(seed_) && seed_ != 0;
	}

	virtual void solve(unsigned int) override
	{
		const Neumann_generator generator;
		const auto lengths = handle_and_cycle_sizes(seed_, generator);
		write_ln(lengths.first + lengths.second);
	}

private:
	unsigned int seed_;
};

MAIN(CP)

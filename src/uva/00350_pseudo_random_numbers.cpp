/*********************************************************************
Pseudo-random numbers
---------------------
UVa ID: 003 50

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"

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

// Returns the cycle length of the transformation (f) orbit
// that starts at the point (x)
template<class Func>
T cycle_length(T x, Func f)
{
	T length = 1;

	const auto p = collision_point(x, f);
	auto p1 = f(p);
	while (p != p1)
	{
		p1 = f(p1);
		++length;
	}

	return length;
}

class Rnd_generator
{
public:
	Rnd_generator(T mult, T inc, T mod) : mult_(mult), inc_(inc), mod_(mod)
	{}

	T operator()(T x) const
	{
		return (mult_ * x + inc_) % mod_;
	}

private:
	const T mult_;
	const T inc_;
	const T mod_;
};

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		read(mult_, inc_, mod_, seed_);
		return (mult_ != 0 || inc_ != 0 || mod_ != 0 || seed_ != 0);
	}

	virtual void solve(unsigned int i_case) override
	{
		const Rnd_generator generator(mult_, inc_, mod_);
		write_ln("Case ", i_case, ": ", cycle_length(seed_, generator));
	}

private:
	unsigned int mult_, inc_, mod_, seed_;
};



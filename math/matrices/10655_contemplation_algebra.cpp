/*********************************************************************
Contemplation! Algebra
----------------------
UVa ID: 10655

Goal:	find (a^n + b^n), given (a+b), (ab) and (n).

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cassert>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

class Contemplation : public CP2
{
private:
	using T = long long;

private:
	virtual bool read_input(std::istream& in) override
	{
		// <p = a + b> <q = a * b> <n>

		in >> p_ >> q_ >> n_;
		return !!in;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		const T f[] = {2, p_};

		if (n_ <= 1)
		{
			out << f[n_] << '\n';
			return;
		}

		/*********************************************************************
		It is easy to show that
			a^n + b^n = p * (a^{n - 1} + b^{n - 1}) -
												- q * (a^{n - 2} + b^{n - 2}),
		where p = a + b and q = a * b.

		Let's denote: f(n) = a^n + b^n.
		
		The recurrence relation:
			f(n) = p * f(n - 1) - q * f(n - 2).

		The base case:
			f(0) = 2 and f(1) = p.
		**********************************************************************/

		Matrix<T> r(2, 2);
		r(0, 0) = p_;
		r(0, 1) = -q_;
		r(1, 0) = 1;
		r(1, 1) = 0;

		r = power(r, n_ - 1);
		out << f[1] * r(0, 0) + f[0] * r(0, 1) << '\n';
	}

private:
	T p_;
	T q_;
	T n_;
};

int main()
{
	Contemplation p;
	return p.run();
}
/*********************************************************************
Riemann vs Mertens
------------------
UVa ID: 107 38

Every positive natural number greater than 1, can be uniquely
decomposed into it's prime factors. Some numbers have only one factor,
namely the number itself, like 2, 11 and 71, and are caled prime
numbers. Others have more than one factor, like 4 (2x2), 15 (3x5)
and 144 (2x2x2x2x3x3), and are called composite numbers. If a number
contains all it's prime factors only once, it is called square free.
All prime numbers are square free. Some composite numbers are square
free, like 21 (3x7) and 187 (11x17), others are not, like 9 (3x3) and
98 (2x7x7). Let's define the Mobius function mu(N), for all positive
natural numbers N:
	mu(1) = 1, by definition;
	if N is not square free, mu(N) = 0;
	if N is square free and contains an even number
		of prime factors, mu(N) = 1;
	if N is square free and contains an odd number
		of prime factors, mu(N) = -1.
Now we can define Mertens's function M(N) as the sum of all mu()
for 1 up to and including N: M(N) = mu(1) + mu(2) + ... + mu(N).
We want you to calculate mu(N) and M(N) for some values of N.

Input
-----
Up to 1'000 numbers between 1 and 1'000'000 (one million), both
included, each on a line by itself. The numbers are in random order
and can appear more than once. Input is terminated by a line, which
contains a single zero. This line should not be processed.

Output
------
For each number in the input print that number, the value of mu()
for that number and the value of M() for that number, all three on
one line, right justified in fields of width 8. The input order must
be preserved.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <vector>

static constexpr auto max_n = 1'000'000;

template<typename T>
T get_smallest_factor(T x)
{
	if (x % 2 == 0)
		return 2;

	const auto sqrt_x = static_cast<T>(std::sqrt(x));
	for (T i = 3; i <= sqrt_x; i += 2)
		if (x % i == 0)
			return i;

	return x;
}

template<typename T>
std::vector<std::pair<T, unsigned int>> factorize(T x)
{
	assert(x > 1);

	std::vector<std::pair<T, unsigned int>> factors;
	while (x > 1)
	{
		const auto base = get_smallest_factor(x);
		unsigned int exp = 0;
		do
		{
			x /= base;
			++exp;
		} while (x % base == 0);

		factors.push_back({base, exp});
	}

	return factors;
}

template<class F>
bool is_square_free(const std::vector<F>& factors)
{
	return std::all_of(factors.begin(), factors.end(),
		[](const F& f) { return f.second == 1; });
}

class CP : public CP2
{
private:
	virtual void init() override
	{
		mobius_.resize(max_n + 1);
		mobius_[0] = 0;
		mobius_[1] = 1;

		for (int i = 2; i <= max_n; ++i)
		{
			const auto factors = factorize(i);
			if (is_square_free(factors))
				mobius_[i] = (factors.size() % 2 == 0) ? 1 : -1;
			else
				mobius_[i] = 0;
		}

		mertens_.resize(max_n + 1);
		std::partial_sum(mobius_.begin(), mobius_.end(), mertens_.begin());
	}

	virtual bool read_input() override
	{
		return read(n_) && n_ != 0;
	}

	virtual void solve(unsigned int) override
	{
		write_ln(std::setw(8), n_, std::setw(8), mobius_[n_], std::setw(8), mertens_[n_]);
	}

private:
	int n_;
	std::vector<int> mobius_;
	std::vector<int> mertens_;
};


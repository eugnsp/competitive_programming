/*********************************************************************
Sum of consecutive prime numbers
--------------------------------
UVa ID: 1210

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "primes.hpp"
#include <vector>
#include <cassert>

class CP : public CP2
{
private:
	using T = unsigned int;
	static constexpr T max_n = 10000;

private:
	virtual void init() override
	{
		primes_ = generate_primes(max_n);
	}

	virtual bool read_input() override
	{
		return read(n_) && n_ != 0;
	}

	virtual void solve(unsigned int) override
	{
		std::size_t n_ways = 0;
		T sum = 0;

		for (auto head = primes_.begin(), tail = head; tail != primes_.end() && *tail <= n_; ++tail)
		{
			sum += *tail;
			while (sum > n_)
			{
				assert(head < tail);
				sum -= *head++;
			}

			if (sum == n_)
				++n_ways;
		}

		write_ln(n_ways);
	}

private:
	T n_;
	std::vector<T> primes_;
};



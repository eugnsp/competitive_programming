/*********************************************************************
Sum of consecutive prime numbers
--------------------------------
UVa ID: 1210

Goal:	find the number of representations of the given integer
		as the sum of one or more consecutive prime numbers.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "primes.hpp"
#include <vector>
#include <cassert>

class Sum_of_primes : public CP2
{
private:
	using T = unsigned int;
	static constexpr T max_prime = 10000;

private:
	virtual void init() override
	{
		primes_ = generate_primes(max_prime);
	}

	virtual bool read_input(std::istream& in) override
	{
		// <n>

		in >> n_;
		if (n_ == 0)
			return false;

		assert(2 <= n_ && n_ <= max_prime);
		return true;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		std::size_t n_ways = 0;
		T sum = 0;

		for (auto head = primes_.begin(), tail = head; 
			tail != primes_.end() && *tail <= n_; ++tail)
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

		out << n_ways << '\n';
	}

private:
	T n_;
	std::vector<T> primes_;
};

int main()
{
	Sum_of_primes p;
	return p.run();
}

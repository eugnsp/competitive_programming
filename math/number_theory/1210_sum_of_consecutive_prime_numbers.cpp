/*********************************************************************
Sum of consecutive prime numbers
--------------------------------
UVa ID: 1210

Goal:	find the number of representations of the given integer
		as the sum of consecutive prime numbers.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <vector>
#include <cassert>

class Sum_of_primes : public CP2
{
private:
	using T = unsigned int;
	static constexpr T max_n_primes = 10000;

private:
	virtual void init() override
	{
		std::vector<bool> is_prime(max_n_primes, true);
		for (T i = 3; i * i < max_n_primes; i += 2)
			for (T j = 3; i * j < max_n_primes; j += 2)
				is_prime[i * j] = false;

		primes_.push_back(2);
		for (T i = 3; i < max_n_primes; i += 2)
			if (is_prime[i])
				primes_.push_back(i);
	}


	virtual bool read_input(std::istream& in) override
	{
		// <integer>

		in >> n_;
		if (n_ == 0)
			return false;

		assert(2 <= n_ && n_ <= max_n_primes);
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
			while (head != tail && sum > n_)
				sum -= *head++;

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

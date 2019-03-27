#pragma once
#include <cassert>
#include <cstddef>
#include <cmath>
#include <vector>
#include <utility>

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
bool is_prime(T x)
{
	if (x <= 3)
		return x >= 2;
	else
		return get_smallest_factor(x) == x;
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

template<typename T>
std::vector<T> generate_primes(T max)
{
	std::vector<T> primes;
	if (max < 2)
		return primes;

	primes.push_back(2);
	const auto is_prime = generate_prime_flags(max);
	for (T i = 3; i <= max; i += 2)
		if (is_prime[i])
			primes.push_back(i);

	return primes;
}

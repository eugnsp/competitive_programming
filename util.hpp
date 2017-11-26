#pragma once

template<typename T>
T power(T base, unsigned int exp)
{
	T r = 1;
	while (exp > 0)
	{
		if (exp & 1u)
			r *= base;
		base *= base;
		exp >>= 1;
	}

	return r;
}

/*********************************************************************
Recurrences
-----------
UVa ID: 108 70

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <vector>
#include <cassert>

using Size = unsigned int;
using T = unsigned int;
using M = Matrix<T, Size>;

// Computes (x) *= (y) modulo m
void modular_prod(M& x, const M& y, T m)
{
	assert(x.cols() == y.rows() && y.rows() == y.cols());

	const auto n = x.rows();
	const auto l = x.cols();
	M res(n, l, 0);

	for (Size j = 0; j < l; ++j)
		for (Size i = 0; i < n; ++i)
			for (Size k = 0; k < l; ++k)
			{
				assert(x(i, k) < m && y(k, j) < m);
				res(i, j) += x(i, k) * y(k, j);
				res(i, j) %= m;
			}

	x = res;
}

// Returns (f(n)) modulo (m), where
// f(n) = a_1 f(n - 1) + ... + a_d f(n - d), n > d
// with a_i = as[i - 1] and f(i) = fs[i - 1]
T fn_mod_m(const std::vector<T>& as, const std::vector<T>& fs, Size n, T m)
{
	if (m == 1)
		return 0;

	const auto d = static_cast<Size>(as.size());
	if (n <= d)
		return fs[n - 1] % m;

	// / f(d+k) \     / a_1 a_2    ... a_d \ k  / f(d) \
	// |  ...   |     |  1   0   0 ...  0  |    | ...  |
	// |  ...   |  =  |  0   1   0 ...  0  |    | ...  |
	// | f(2+k) |     |        ...         |    | f(2) |
	// \ f(1+k) /     \  0   0 ...  1   0  /    \ f(1) /

	Matrix<T, Size> b(d, d, 0);

	for (Size i = 0; i < d; ++i)
		b(i, 0) = as[i] % m;

	for (Size i = 1; i < d; ++i)
		b(i - 1, i) = 1;

	auto exp = n - d - 1;
	auto b_to_exp = b;

	while (exp > 0)
	{
		if (exp & 1u)
			modular_prod(b_to_exp, b, m);

		modular_prod(b, b, m);
		exp >>= 1;
	}

	Matrix<T, Size> f(1, d);

	for (Size i = 0; i < d; ++i)
		f(0, i) = fs[d - i - 1] % m;

	modular_prod(f, b_to_exp, m);
	return f(0, 0);
}

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		Size d;

		read(d, n_, m_);
		if (d == 0 && n_ == 0 && m_ == 0)
			return false;

		assert(1 <= d && d <= 15);
		assert(1 <= n_);
		assert(1 <= m_ && m_ * m_ <= (1U << 31));
		
		return read_vec(d, as_) && read_vec(d, fs_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(fn_mod_m(as_, fs_, n_, m_));
	}

private:
	Size n_;
	T m_;
	std::vector<T> as_;
	std::vector<T> fs_;
};

MAIN(CP)


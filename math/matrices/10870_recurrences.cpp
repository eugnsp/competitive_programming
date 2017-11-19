/*********************************************************************
Recurrences
-----------
UVa ID: 10870

Goal:	compute f(n) mod m.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <cstdint>
#include <vector>
#include <cassert>

class Recurrences : public CP2
{
private:
	using T = std::uint32_t;

private:
	virtual bool read_input(std::istream& in) override
	{
		// <d> <n> <m>
		// <a_1> ... <a_d>
		// <f(1)> ... <f(d)>

		in >> d_ >> n_ >> m_;
		if (d_ == 0 && n_ == 0 && m_ == 0)
			return false;

		assert(1 <= d_ && d_ <= 15);
		assert(1 <= n_);
		assert(1 <= m_ && m_ <= 46340);		// 46340 = floor(sqrt(INT_MAX))

		as_.resize(d_);
		fs_.resize(d_);

		for (auto& a : as_)
			in >> a;

		for (auto& f : fs_)
			in >> f;

		return true;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
 		if (m_ == 1)
 		{
 			out << "0\n";
 			return;
 		}
		
		if (n_ <= d_)
		{
			out << fs_[n_ - 1] % m_ << '\n';
			return;
		}

		/*********************************************************************
		If f(n) is given by			
			f(n) = a_1 f(n - 1) + ... + a_d f(n - d), n > d,
		then
		                                         k
			/ f(d+k) \     / a_1 a_2    ... a_d \    / f(d) \
			|  ...   |     |  1   0   0 ...  0  |    | ...  |
			|  ...   |  =  |  0   1   0 ...  0  |    | ...  | .
			| f(2+k) |     |        ...         |    | f(2) |
			\ f(1+k) /     \  0   0 ...  1   0  /    \ f(1) /
		**********************************************************************/

		Matrix<T> b(d_, d_, 0);
		
		for (std::size_t i = 0; i < d_; ++i)
			b(i, 0) = as_[i] % m_;

		for (std::size_t i = 1; i < d_; ++i)
			b(i - 1, i) = 1;

		auto exp = n_ - d_ - 1;
		auto b_to_exp = b;

		while (exp > 0)
		{
			if (exp & 1u)
				modular_prod(b_to_exp, b);

			modular_prod(b, b);
			exp >>= 1;
		}

		Matrix<T> f(1, d_);
		
		for (std::size_t i = 0; i < d_; ++i)
			f(0, i) = fs_[d_ - i - 1] % m_;

		modular_prod(f, b_to_exp);
		out << f(0, 0) << '\n';
	}

	// Computes (x *= y) in modular arithmetic
	void modular_prod(Matrix<T>& x, const Matrix<T>& y) const
	{
		assert(x.cols() == y.rows() && y.rows() == y.cols());

		const auto n = x.rows();
		const auto m = x.cols();
		Matrix<T> res(n, m, 0);

		for (std::size_t j = 0; j < m; ++j)
			for (std::size_t i = 0; i < n; ++i)
				for (std::size_t k = 0; k < m; ++k)
				{
					assert(x(i, k) < m_ && y(k, j) < m_);
					res(i, j) += x(i, k) * y(k, j);
					res(i, j) %= m_;
				}

		x = res;
	}

private:
	std::size_t d_;
	T n_;
	T m_;
	std::vector<T> as_;
	std::vector<T> fs_;
};

int main()
{
	Recurrences p;
	return p.run();
}



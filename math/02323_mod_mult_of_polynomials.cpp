/*********************************************************************
Modular multiplication of polynomials
-------------------------------------
UVa Live ID: 2323

Goal:	given three polynomials f(x), g(x) and h(x) over field GF(2),
		compute	f(x) g(x) mod h(x).

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <vector>
#include <cassert>

class Mod_mult_of_polynomials : public CP1
{
private:
	class Poly
	{
	public:
		std::size_t degree() const
		{
			return coeffs_.size() - 1;
		}

		friend Poly operator*(const Poly& x, const Poly& y)
		{
			const auto dx = x.degree();
			const auto dy = y.degree();

			Poly z;
			z.coeffs_.resize(dx + dy + 1, 0);
			for (std::size_t i = 0; i <= dx; ++i)
				for (std::size_t j = 0; j <= dy; ++j)
					z.coeffs_[i + j] ^= (x.coeffs_[i] & y.coeffs_[j]);

			return z;
		}

		friend Poly operator%(Poly x, const Poly& y)
		{
			auto& xc = x.coeffs_;
			auto& yc = y.coeffs_;

			while (x.degree() >= y.degree())
			{
				for (std::size_t i = 0; i <= y.degree(); ++i)
					xc[i] ^= yc[i];

				const auto leading_one_pos = std::find(xc.begin(), xc.end(), 1);
				if (leading_one_pos != xc.end())
					xc.erase(xc.begin(), leading_one_pos);
				else
				{
					xc.resize(1);
					return x;
				}
			}

			return x;
		}

		friend std::istream& operator>>(std::istream& in, Poly& poly)
		{
			std::size_t n;
			in >> n;
			assert(n > 0);

			poly.coeffs_.resize(n);
			for (auto& c : poly.coeffs_)
				in >> c;
			
			return in;
		}

		friend std::ostream& operator<<(std::ostream& out, const Poly& poly)
		{
			out << poly.coeffs_.size();
			for (auto c : poly.coeffs_)
				out << ' ' << c;

			return out;
		}

	private:
		std::vector<unsigned int> coeffs_;
	};

private:
	virtual void read_input(std::istream& in) override
	{
		// <order of f(x) = fn> <f_fn> ... <f_0>
		// <order of g(x) = gn> <g_gn> ... <g_0>
		// <order of h(x) = hn> <h_hn> ... <h_0>

		in >> f_;
		in >> g_;
		in >> h_;

		assert(f_.degree() < 1000);
		assert(g_.degree() < 1000);
		assert(h_.degree() < 1000);
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		out << (f_ * g_) % h_ << '\n';
	}

private:
	Poly f_;
	Poly g_;
	Poly h_;
};

int main()
{
	Mod_mult_of_polynomials p;
	return p.run();
}

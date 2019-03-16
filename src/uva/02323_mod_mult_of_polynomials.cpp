/*********************************************************************
Modular multiplication of polynomials
-------------------------------------
UVa Live ID: 023 23

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <vector>
#include <cassert>

class CP : public CP1
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

		friend void read(Poly& poly)
		{
			std::size_t n;
			read(n);
			assert(n > 0);

			poly.coeffs_.resize(n);
			for (auto& c : poly.coeffs_)
				read(c);
		}

		friend void write(const Poly& poly)
		{
			write(poly.coeffs_.size());
			for (auto c : poly.coeffs_)
				write(' ', c);
		}

	private:
		std::vector<unsigned int> coeffs_;
	};

private:
	virtual void read_input() override
	{
		read(f_);
		read(g_);
		read(h_);

		assert(f_.degree() < 1000);
		assert(g_.degree() < 1000);
		assert(h_.degree() < 1000);
	}

	virtual void solve(unsigned int) override
	{
		write((f_ * g_) % h_);
		write_ln();
	}

private:
	Poly f_;
	Poly g_;
	Poly h_;
};



/*********************************************************************
Modular multiplication of polynomials
-------------------------------------
UVa Live ID: 023 23

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

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

			while (true)
			{
				auto it_x = std::find(xc.begin(), xc.end(), 1u);
				if (static_cast<std::size_t>(xc.end() - it_x) <= y.degree())
					break;

				for (auto it_y = yc.begin(); it_y != yc.end(); ++it_y, ++it_x)
					*it_x ^= *it_y;
			}

			const auto leading_one = std::find(xc.begin(), xc.end(), 1u);
			if (leading_one == xc.end())
				xc.resize(1, 0);
			else
				xc.erase(xc.begin(), leading_one);

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

MAIN


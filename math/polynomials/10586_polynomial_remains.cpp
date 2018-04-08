/*********************************************************************
Polynomial remains
------------------
UVa ID: 105 86

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "io.hpp"
#include <vector>

using Order = unsigned int;
using T = int;
using Poly = std::vector<T>;

// Removes all trailing zeros from the representation of the (poly)nomial
void chomp_zeros(Poly& poly)
{
	while (poly.size() > 1 && poly.back() == 0)
		poly.pop_back();
}

// Returns the remainder of division of the (poly)nomial
// by the polynomial (x^k - 1)
Poly remainder(Poly poly, Order k)
{
	if (poly.size() <= k)
	{
		chomp_zeros(poly);
		return poly;
	}

	for (auto it = poly.rbegin(); it != poly.rend() - k; ++it)
	{
		*(it + k) -= *it;
		*it = 0;
	}

	chomp_zeros(poly);
	return poly;
}

class CP : public CP2
{
private:
	virtual bool read_input(std::istream& in) override
	{
		T n, k;
		in >> n >> k;
		if (n == -1 && k == -1)
			return false;

		assert(0 <= n && n <= 10000);
		assert(0 <= k && k <= 10000);

		read_vector(in, n + 1, poly_);
		k_ = static_cast<Order>(k);

		return true;
	}

	virtual void solve(std::ostream& out, unsigned int) const override
	{
		const auto rem = remainder(poly_, k_);
		print_join(out, rem.begin(), rem.end());
		out << '\n';
	}

private:
	Poly poly_;
	Order k_;
};

int main()
{
	CP p;
	return p.run();
}

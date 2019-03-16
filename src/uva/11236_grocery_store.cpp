/*********************************************************************
Grocery store
-------------
UVa ID: 112 36

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <iomanip>

class CP : public CP3
{
private:
	virtual void read_input() override
	{}

	virtual void solve() override
	{
		write(std::fixed, std::setprecision(2));

		for (unsigned int w = 1; w <= 5'00; ++w)
			for (unsigned int x = w; 3 * x <= 20'00 - w; ++x)
			{
				const auto wx = w * x;
				const auto w_x = w + x;

				for (unsigned int y = x; 2 * y <= 20'00 - w_x; ++y)
				{
					const auto wxy = wx * y;

					// z = 100^3 * w_x_y / (wxy - 100^3) should be a positive integer
					if (wxy <= 1'00'00'00)
						continue;

					const auto w_x_y = w_x + y;
					const auto num = 100'00'00ULL * w_x_y;
					const auto denom = wxy - 100'00'00;

					if (num % denom != 0)
						continue;

					const auto z = num / denom;
					if (z < y || w_x_y + z > 2000)
						continue;

					write_ln(w / 100., ' ', x / 100., ' ', y / 100., ' ', z / 100.);
				}
			}
	}
};



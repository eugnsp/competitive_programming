/*********************************************************************
Y2K accounting bug
------------------
UVa ID: 10576

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

// Note: a much clever solution without iterative search exists.

#include "base.hpp"
#include "bit.hpp"

using Mask = unsigned int;

int max_surplus(unsigned int surplus, unsigned int deficit)
{
	constexpr auto n_months = 12U;
	constexpr auto n_consecutive_months = 5U;

	auto sd_mask = n_ls_bits<Mask>(n_months);

	const auto month_surplus = [surplus, deficit, &sd_mask](unsigned int month)
	{
		return is_bit_set(sd_mask, month) ?
			static_cast<int>(surplus) : -static_cast<int>(deficit);
	};

	int max = -1;
	while (sd_mask)
	{
		int total_sum = 0;
		int consecutive_sum = 0;

		for (unsigned int k = 0; k < n_months; ++k)
		{
			const auto m = month_surplus(k);
			total_sum += m;
			consecutive_sum += m;

			if (k >= n_consecutive_months - 1)
			{
				if (k >= n_consecutive_months)
					consecutive_sum -= month_surplus(k - n_consecutive_months);

				if (consecutive_sum >= 0)
					goto try_next_mask;
			}
		}

		if (max < total_sum)
			max = total_sum;

	try_next_mask:
		--sd_mask;
	}

	return max;
}

class CP : public CP2
{
private:
	virtual bool read_input(std::istream& in) override
	{
		auto sd_mask = n_ls_bits<Mask>(6);

		return !!(in >> surplus_ >> deficit_);
	}

	virtual void solve(std::ostream& out, std::size_t) const override
	{
		const auto surplus = max_surplus(surplus_, deficit_);
		if (surplus >= 0)
			out << surplus << '\n';
		else
			out << "Deficit\n";
	}

private:
	unsigned int surplus_;
	unsigned int deficit_;
};

int main()
{
	CP p;
	return p.run();
}

/*********************************************************************
Fill the containers
-------------------
UVa ID: 114 13

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <numeric>
#include <vector>

using Size = unsigned int;
using Capacity = unsigned int;

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		vessel_capacities_.clear();

		Size n_vessels;
		return read(n_vessels) && read(n_containers_) && read_vec(n_vessels, vessel_capacities_);
	}

	virtual void solve(unsigned int) override
	{
		Capacity capacity_lb = 0;
		Capacity capacity_rb = total_vessels_capacity();
		while (capacity_rb > capacity_lb)
		{
			const auto capacity = (capacity_lb + capacity_rb) / 2;
			if (is_valid_min_capacity(capacity))
				capacity_rb = capacity;
			else
				capacity_lb = capacity + 1;
		}

		write_ln(capacity_rb);
	}

	bool is_valid_min_capacity(Capacity capacity) const
	{
		Size n_used_containers = 1;
		Capacity curr = 0;

		for (auto vc : vessel_capacities_)
		{
			if (vc > capacity)
				return false;

			curr += vc;
			if (curr > capacity)
			{
				curr = vc;
				if (++n_used_containers > n_containers_)
					return false;
			}
		}

		return true;
	}

	Capacity total_vessels_capacity() const
	{
		return std::accumulate(
			vessel_capacities_.begin(), vessel_capacities_.end(), static_cast<Capacity>(0));
	}

private:
	Size n_containers_;
	std::vector<Capacity> vessel_capacities_;
};

MAIN(CP)

/*********************************************************************
Budget travel
-------------
UVa ID: 002 22

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <cassert>
#include <cstddef>
#include <iomanip>
#include <vector>

struct Station
{
	double distance;
	double price;
};

class Budget_travel
{
public:
	Budget_travel(
		double distance,
		double tank_capacity,
		double miles_per_gallon,
		double cost,
		const std::vector<Station>& stations) :
		distance_(distance),
		tank_capacity_(tank_capacity), miles_per_gallon_(miles_per_gallon), init_cost_(cost),
		stations_(stations)
	{}

	double min_price() const
	{
		return init_cost_ + min_price(tank_capacity_, 0);
	}

private:
	double min_price(double remaining_fuel, unsigned int station) const
	{
		constexpr auto cents_in_dollar = 100;
		constexpr double snack_price = 2.00;

		remaining_fuel -= get_distance_covered(station) / miles_per_gallon_;
		assert(remaining_fuel >= 0);

		const auto fuel_to_next = get_distance_to_next(station) / miles_per_gallon_;
		const bool enough_fuel_to_next = (remaining_fuel >= fuel_to_next);
		const double fuel_price =
			(tank_capacity_ - remaining_fuel) * stations_[station].price / cents_in_dollar;

		if (next_station_exists(station))
		{
			const bool no_stop = (remaining_fuel > tank_capacity_ / 2) && enough_fuel_to_next;
			if (no_stop)
				return min_price(remaining_fuel, station + 1);

			const double with_stop =
				snack_price + fuel_price + min_price(tank_capacity_, station + 1);
			if (!enough_fuel_to_next)
				return with_stop;

			const double without_stop = min_price(remaining_fuel, station + 1);
			return std::min(with_stop, without_stop);
		}
		else
			return enough_fuel_to_next ? 0 : snack_price + fuel_price;
	}

	double get_distance_covered(unsigned int station) const
	{
		if (station == 0)
			return stations_.front().distance;
		else
			return stations_[station].distance - stations_[station - 1].distance;
	}

	double get_distance_to_next(unsigned int station) const
	{
		if (next_station_exists(station))
			return stations_[station + 1].distance - stations_[station].distance;
		else
			return distance_ - stations_.back().distance;
	}

	bool next_station_exists(unsigned int station) const
	{
		return station + 1 < stations_.size();
	}

private:
	const double distance_;
	const double tank_capacity_;
	const double miles_per_gallon_;
	const double init_cost_;
	const std::vector<Station>& stations_;
};

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		if (!read(distance_) || distance_ < 0)
			return false;

		std::size_t n_stations;
		read(tank_capacity_, miles_per_gallon_, init_cost_, n_stations);

		assert(n_stations <= 50);
		stations_.resize(n_stations);

		for (auto& s : stations_)
		{
			read(s.distance, s.price);
			assert(s.distance <= distance_);
		}

		return true;
	}

	virtual void solve(unsigned int i_case) override
	{
		const Budget_travel travel(
			distance_, tank_capacity_, miles_per_gallon_, init_cost_, stations_);
		write_ln("Data Set #", i_case + 1);
		write_ln("minimum cost = $", std::fixed, std::setprecision(2), travel.min_price());
	}

private:
	double distance_;
	double tank_capacity_;
	double miles_per_gallon_;
	double init_cost_;
	std::vector<Station> stations_;
};

MAIN(CP)

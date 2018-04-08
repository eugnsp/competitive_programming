/*********************************************************************
Wetlands of Florida
-------------------
UVa ID: 004 69

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include "position.hpp"
#include <array>
#include <cassert>
#include <string>
#include <sstream>
#include <vector>
#include <utility>

using Size = unsigned int;
using Pos = Position<Size>;
using Landscape = Matrix<bool, Size>;

class Flood_fill_area
{
public:
	Flood_fill_area(const Landscape& landscape)
		: landscape_(landscape)
	{
		visited_.resize(landscape_.rows(), landscape_.cols());
	}

	Size flood_fill_area(Pos pos) const
	{
		assert(is_inside(pos) && landscape_(pos));

		visited_.fill(false);
		return flood_fill_area_impl(pos);
	}

private:
	Size flood_fill_area_impl(Pos pos) const
	{
		visited_(pos) = true;

		Size area = 1;
		for (auto new_pos : eight_neighbours(pos))
			if (is_inside(new_pos) && !visited_(new_pos) && landscape_(new_pos))
				area += flood_fill_area_impl(new_pos);

		return area;
	}

	static std::array<Pos, 8> eight_neighbours(Pos pos)
	{
		constexpr auto m = static_cast<Size>(-1);
		
		std::array<Pos, 8> neighbours = {m, m, 0, m, 1, m, 1, 0, 1, 1, 0, 1, m, 1, m, 0};
		for (auto& neighbour : neighbours)
			neighbour += pos;

		return neighbours;
	}

	bool is_inside(Pos pos) const
	{
		return pos.row < landscape_.rows() && pos.col < landscape_.cols();
	}

private:
	const Landscape& landscape_;
	mutable Landscape visited_;
};

class CP : public CP1
{
private:
	virtual void read_input(std::istream& in) override
	{
		if (wet_landscape_.rows() == 0)
			ignore_line(in);

		std::string str;
		std::vector<std::vector<bool>> landscape;

		queries_.clear();
		while (std::getline(in, str) && !str.empty())
		{
			if (str.front() == 'L' || str.front() == 'W')
			{
				std::vector<bool> line;
				for (auto c : str)
					line.push_back(c == 'W');
				landscape.push_back(std::move(line));
			}
			else
			{
				Pos pos;
				std::istringstream ss(str);
				ss >> pos.col >> pos.row;		// Matrix (wet_landscape_) is transposed on construction
				--pos.row;						// To zero-based indexing
				--pos.col;
				queries_.push_back(pos);
			}
		}

		wet_landscape_ = Landscape{landscape};
	}

	virtual void solve(std::ostream& out, unsigned int i_case) const override
	{
		if (i_case > 0)
			out << '\n';

		const Flood_fill_area wetland(wet_landscape_);
		for (auto q : queries_)
			out << wetland.flood_fill_area(q) << '\n';
	}

private:
	Landscape wet_landscape_;
	std::vector<Pos> queries_;
};

int main()
{
	CP p;
	return p.run();
}

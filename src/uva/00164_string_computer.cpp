/*********************************************************************
String computer
---------------
UVa ID: 001 64

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_edit_distance.hpp"
#include <cstddef>
#include <string>
#include <iomanip>

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read(str_from_, str_to_) && str_from_ != "#";
	}

	virtual void solve(unsigned int) override
	{
		const auto dist = edit_distance_and_sequence(str_from_, str_to_);
		for (auto& op : dist.second)
		{
			switch (op.operation)
			{
			case Operations::REPLACE:
				write('C', str_to_[op.position_to - 1], std::setw(2), op.position_to);
				break;

			case Operations::INSERT:
				write('I', str_to_[op.position_to - 1], std::setw(2), op.position_to);
				break;

			case Operations::DELETE:
				write('D', str_from_[op.position_from - 1], std::setw(2), op.position_to + 1);
			}
		}

		write_ln('E');
	}

private:
	std::string str_from_;
	std::string str_to_;
};



/*********************************************************************
String distance and transform process
-------------------------------------
UVa ID: 005 26

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_edit_distance.hpp"
#include <cstddef>
#include <string>

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		return read_ln(str_from_) && read_ln(str_to_);
	}

	virtual void solve(unsigned int i_case) override
	{
		if (i_case > 0)
			write_ln();

		const auto dist = edit_distance_and_sequence(str_from_, str_to_);
		write_ln(dist.first);

		std::size_t i = 1;
		for (auto& op : dist.second)
		{
			if (op.operation == Operations::MATCH)
				continue;

			write(i++, ' ');
			switch (op.operation)
			{
			case Operations::REPLACE:
				write("Replace ", op.position_to, ',', str_to_[op.position_to - 1]);
				break;

			case Operations::INSERT:
				write("Insert ", op.position_to, ',', str_to_[op.position_to - 1]);
				break;

			case Operations::DELETE:
				write("Delete ", op.position_to + 1);
				break;
			}
			write_ln();
		}
	}

private:
	std::string str_from_;
	std::string str_to_;
};

MAIN(CP)

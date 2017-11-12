/*********************************************************************
String distance and transform process
-------------------------------------
UVa ID: 526

Goal:	calculate the distance between two strings and
		the corresponding edit sequence.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_edit_distance.hpp"
#include <cstddef>
#include <string>

class String_distance : public CP2
{
private:
	virtual bool read_input(std::istream& in) override
	{
		// <from string>
		// <to string>

		std::getline(in, str_from_);
		std::getline(in, str_to_);

		return !!in;
	}

	virtual void solve(std::ostream& out, std::size_t i_case) override
	{
		if (i_case > 0)
			out << '\n';

		const auto dist = edit_distance_and_sequence(str_from_, str_to_);
		out << dist.first << '\n';

		std::size_t i = 1;
		for (auto& op : dist.second)
		{
			if (op.operation == Operations::MATCH)
				continue;

			out << i++ << ' ';
			switch (op.operation)
			{
			case Operations::REPLACE:
				out << "Replace " << op.position_to << ',' << str_to_[op.position_to - 1];
				break;

			case Operations::INSERT:
				out << "Insert " << op.position_to << ',' << str_to_[op.position_to - 1];
				break;

			case Operations::DELETE:
				out << "Delete " << op.position_to + 1;
				break;
			}
			out << '\n';
		}
	}

private:
	std::string str_from_;
	std::string str_to_;
};

int main()
{
	String_distance p;
	return p.run();
}

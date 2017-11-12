/*********************************************************************
String computer
---------------
UVa ID: 164

Goal:	calculate the distance between two strings and
		the corresponding edit sequence.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "dp_edit_distance.hpp"
#include <cstddef>
#include <string>
#include <iomanip>

class String_computer : public CP2
{
private:
	virtual bool read_input(std::istream& in) override
	{
		// <from string>
		// <to string>

		in >> str_from_ >> str_to_;
		return (str_from_ != "#");
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		const auto dist = edit_distance_and_sequence(str_from_, str_to_);
		for (auto& op : dist.second)
		{
			switch (op.operation)
			{
			case Operations::REPLACE:
				out << 'C' << str_to_[op.position_to - 1]	<< std::setw(2) << op.position_to;
				break;

			case Operations::INSERT:
				out << 'I' << str_to_[op.position_to - 1] << std::setw(2) << op.position_to;
				break;

			case Operations::DELETE:
				out << 'D' << str_from_[op.position_from - 1]	<< std::setw(2) << op.position_to + 1;
			}
		}

		out << "E\n";
	}

private:
	std::string str_from_;
	std::string str_to_;
};

int main()
{
	String_computer p;
	return p.run();
}
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
#include <iostream>

class String_distance : public CP2
{
private:
	virtual bool read_input() override
	{
		// <from string>
		// <to string>

		std::getline(std::cin, str_from_);
		std::getline(std::cin, str_to_);

		return !!std::cin;
	}

	virtual void solve(std::size_t i_case) override
	{
		if (i_case > 0)
			std::cout << '\n';

		const auto dist = edit_distance_and_sequence(str_from_, str_to_);
		std::cout << dist.first << '\n';

		std::size_t i = 1;
		for (auto& op : dist.second)
		{
			if (op.operation == Operations::MATCH)
				continue;

			std::cout << i++ << ' ';
			switch (op.operation)
			{
			case Operations::REPLACE:
				std::cout << "Replace " << op.position_to << ',' << str_to_[op.position_to - 1];
				break;

			case Operations::INSERT:
				std::cout << "Insert " << op.position_to << ',' << str_to_[op.position_to - 1];
				break;

			case Operations::DELETE:
				std::cout << "Delete " << op.position_to + 1;
				break;
			}
			std::cout << '\n';
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

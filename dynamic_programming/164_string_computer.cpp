// String computer
// ---------------
//
// Goal: calculate the distance between two strings and the corresponding edit sequence.
//
// UVa ID: 164
// This file is covered by the LICENSE file in the root of this project.

#include "dp_edit_distance.hpp"
#include <cstddef>
#include <string>
#include <iostream>
#include <iomanip>

// <from string>
// <to string>

int main()
{
	std::cout << std::setfill('0');

	for (;;)
	{
		std::string sf, st;
		std::cin >> sf >> st;

		if (sf == "#" || !std::cin)
			break;
		
		const auto dist = edit_distance_and_sequence(sf, st);
		for (auto& op : dist.second)
		{
			switch (op.operation)
			{
			case Operations::REPLACE:
				std::cout << 'C' << st[op.position_to - 1] << std::setw(2) << op.position_to;
				break;

			case Operations::INSERT:
				std::cout << 'I' << st[op.position_to - 1] << std::setw(2) << op.position_to;
				break;

			case Operations::DELETE:
				std::cout << 'D' << sf[op.position_from - 1] << std::setw(2) << op.position_to + 1;
			}
		}
		std::cout << "E\n";
	}

	return 0;
}
// String distance and transform process
// -------------------------------------
//
// Goal: calculate the distance between two strings and the corresponding edit sequence.
//
// UVa ID: 526
// This file is covered by the LICENSE file in the root of this project.

#include "edit_distance.hpp"
#include <cstddef>
#include <string>
#include <iostream>

using T = unsigned int;

// <from string>
// <to string>

int main()
{
	for (bool first = true; ; first = false)
	{
		std::string sf, st;
		std::getline(std::cin, sf);
		std::getline(std::cin, st);

		if (!std::cin)
			break;

		if (!first)
			std::cout << '\n';

		const auto dist = edit_distance_and_sequence<T>(sf, st);
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
				std::cout << "Replace " << op.position_to << ',' << st[op.position_to - 1];
				break;

			case Operations::INSERT:
				std::cout << "Insert " << op.position_to << ',' << st[op.position_to - 1];
				break;

			case Operations::DELETE:
				std::cout << "Delete " << op.position_to + 1;
				break;
			}
			std::cout << '\n';
		}
	}

	return 0;
}
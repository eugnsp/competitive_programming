/*********************************************************************
Row with max 1s
---------------
URL: https://practice.geeksforgeeks.org/problems/row-with-max-1s/0

Given a boolean 2D array where each row is sorted. Find the row with
the maximum number of 1s.

Input
-----
The first line of input contains an integer T denoting the number of
test cases. The first line of each test case contains n and m, where
n is the number of rows and m is the number of columns. The second
line of each test case contains the array elements.

Output
------
Print the row with the maximum number of 1s.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <algorithm>
#include <vector>

template<typename T>
std::size_t row_with_max_number_of_1s(const std::vector<T>& mat, std::size_t rows)
{
	std::size_t max_row = 0;
	std::size_t max_n = 0;

	const auto cols = mat.size() / rows;
	for (std::size_t row = 0; row < rows; ++row)
	{
		const auto first = mat.begin() + row * cols;
		if (first[cols - max_n - 1] == 0)
			continue;

		const auto last = mat.begin() + (row + 1) * cols;
		auto pos = std::lower_bound(first, last - max_n, 1);
		const auto n = static_cast<std::size_t>(last - pos);
		if (n > max_n)
		{
			if (n == cols)
				return row;
			max_n = n;
			max_row = row;
		}
	}

	return max_row;
}

template<typename T>
std::size_t row_with_max_number_of_1s2(const std::vector<T>& mat, std::size_t rows)
{
	const auto cols = mat.size() / rows;

	std::size_t max_row = 0;
	auto max_n = 0;

	for (std::size_t row = 0; row < rows; ++row)
	{
		const auto first = mat.begin() + row * cols;
		if (first[cols - max_n - 1] == 0)
			continue;

		auto it = first + cols - max_n;
		while (it != first && *(it - 1) == 1)
		{
			++max_n;
			--it;
		}

		if (max_n == cols)
			return row;
		max_row = row;
	}

	return max_row;
}

using T = int;

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t rows;
		read(rows, cols_);

		mat_.clear();
		mat_.reserve(rows * cols_);
		read_vec(rows * cols_, mat_);
	}

	virtual void solve(unsigned int) override
	{
		write_ln(row_with_max_number_of_1s(mat_, cols_));
	}

private:
	std::vector<T> mat_;
	std::size_t cols_;
};

MAIN(CP)

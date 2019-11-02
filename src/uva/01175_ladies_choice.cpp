/*********************************************************************
Ladies' choice
--------------
UVa ID: 011 75

Teenagers from the local high school have asked you to help them with
the organization of next year's Prom. The idea is to find a suitable
date for everyone in the class in a fair and civilized way. So, they
have organized a web site where all students, boys and girls, state
their preferences among the class members by ordering all the possible
candidates. Your mission is to keep everyone as happy aspossible.
Assume that there are equal numbers of boys and girls. Given a set
of preferences, set up the blind dates such that there are no other
two people of oppositesex who would both rather have each other than
their current partners. Since it was decided that the Prom was Ladies'
Choice, we want to produce the best possible choice for the girls.

Input
-----
Input consists of multiple test cases the first line of the input
contains the number of test cases. There is a blank line before each
dataset. The input for each dataset consists of a positive integer N,
not greater than 1'000, indicating the number of couples in the class.
Next, there are N lines, each one containing the all the integers from
1 to N, ordered according to the girl's preferences. Next, there are
N lines, each one containing all the integers from 1 to N, ordered
according to the boy's preferences.

Output
------
The output for each dataset consists of a sequence of N lines, where
the i-th line contains the number of the boy assigned to the i-th girl
(from 1 to N). Print a blank line between datasets.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cassert>
#include <cstddef>
#include <utility>
#include <vector>

template<typename T>
std::vector<T> stable_match(const Matrix<T>& prefs1, const Matrix<T>& prefs2)
{
	const auto n = static_cast<T>(prefs1.rows());
	assert(n == prefs1.cols() && n == prefs2.rows() && n == prefs2.cols());

	Matrix<T> ranks2(n, n);
	for (T elem2 = 0; elem2 < n; ++elem2)
		for (T rank2 = 0; rank2 < n; ++rank2)
		{
			const auto elem1 = prefs2(rank2, elem2);
			ranks2(elem1, elem2) = rank2;
		}

	constexpr auto free = static_cast<T>(-1);

	std::vector<T> match1(n, free);
	std::vector<T> match2(n, free);

	std::vector<typename Matrix<T>::Col_const_iterator> its1;
	its1.reserve(n);
	for (T elem1 = 0; elem1 < n; ++elem1)
		its1.push_back(prefs1.begin_col(elem1));

	for (T next1 = 0; next1 < n; ++next1)
	{
		auto elem1 = next1;
		do
		{
			const auto elem2 = *its1[elem1]++;
			while (elem1 != free &&
				   (match2[elem2] == free || ranks2(elem1, elem2) < ranks2(match2[elem2], elem2)))
			{
				match1[elem1] = elem2;
				std::swap(match2[elem2], elem1);
			}
		} while (elem1 != free);
	}

	return match1;
}

class CP : public CP1
{
private:
	virtual void read_input() override
	{
		std::size_t n_couples;
		read(n_couples);

		girls_prefs_.resize(n_couples, n_couples);
		boys_prefs_.resize(n_couples, n_couples);

		const auto to_zero_based = [](std::size_t i) { return i - 1; };
		read_transposed_matrix(girls_prefs_, to_zero_based);
		read_transposed_matrix(boys_prefs_, to_zero_based);
	}

	virtual void solve(unsigned int i_case) override
	{
		if (i_case > 1)
			write_ln();

		const auto match = stable_match(girls_prefs_, boys_prefs_);

		const auto to_one_based = [](std::size_t i) { return i + 1; };
		write_range(match.begin(), match.end(), to_one_based, '\n');
		write_ln();
	}

private:
	Matrix<std::size_t> girls_prefs_;
	Matrix<std::size_t> boys_prefs_;
};

MAIN

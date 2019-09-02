/*********************************************************************
Sum it up
---------
UVa ID: 005 74

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "bit.hpp"
#include <cassert>
#include <cstddef>
#include <string>
#include <utility>
#include <vector>

using Number = unsigned int;

class Sum_it_up
{
private:
	using Sums = std::vector<std::string>;
	using Bit_mask = unsigned int;

public:
	Sum_it_up(const std::vector<Number>& numbers, Number total) : numbers_(numbers), total_(total)
	{}

	Sums enumerate_sums() const
	{
		const auto n_numbers = numbers_.size();
		std::vector<Bit_mask> masks;

		find_next(masks, Bit_mask(n_numbers), 0, 0);

		Sums sums;
		for (const auto& mask : masks)
		{
			assert(mask);

			std::string sum;
			for (std::size_t i = 0; i < n_numbers; ++i)
				if (is_bit_set(mask, i))
					sum += std::to_string(numbers_[i]) + '+';

			sum.pop_back();
			sums.push_back(std::move(sum));
		}

		return sums;
	}

private:
	void find_next(std::vector<Bit_mask>& sums, Bit_mask selected, Number sum, std::size_t pos) const
	{
		while (pos < numbers_.size())
		{
			const bool can_select_at_pos = (pos == 0) || is_bit_set(selected, pos - 1) || !adjacent_equal(pos - 1);

			if (can_select_at_pos)
			{
				const auto new_sum = sum + numbers_[pos];
				if (new_sum == total_)
					sums.push_back(with_bit_set(selected, pos));
				else if (new_sum < total_)
					find_next(sums, with_bit_set(selected, pos), new_sum, pos + 1);
			}

			++pos;
		}
	}

	bool adjacent_equal(std::size_t pos) const
	{
		return numbers_[pos] == numbers_[pos + 1];
	}

private:
	const std::vector<Number>& numbers_;
	const Number total_;
};

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		read(total_);
		assert(total_ < 1000);

		return read_size_vec(numbers_);
	}

	virtual void solve(unsigned int) override
	{
		const Sum_it_up sums(numbers_, total_);
		const auto ss = sums.enumerate_sums();

		write_ln("Sums of ", total_, ':');
		for (const auto& sum : ss)
			write_ln(sum);
		if (ss.empty())
			write_ln("NONE");
	}

private:
	Number total_;
	std::vector<Number> numbers_;
};

MAIN


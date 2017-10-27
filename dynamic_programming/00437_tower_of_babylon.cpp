/*********************************************************************
The tower of Babylon
--------------------
UVa ID: 437

Goal:	determine the height of the tallest tower that can be
		built with a given set of blocks.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

class Babylon : public CP2
{
private:
	using T = unsigned int;
	static constexpr T max_size = static_cast<T>(-1);

	struct Base
	{
		T x;
		T y;
	};

	struct Block
	{
		T size[3];

		Base base(unsigned int j) const
		{
			assert(j < 3);
			return {size[(j + 1) % 3], size[(j + 2) % 3]};
		}

		T height(unsigned int j) const
		{
			assert(j < 3);
			return size[j];
		}
	};

private:
	virtual bool read_input() override
	{
		// <number of blocks>
		// <x_1> <y_1> <z_1>
		// ...
		// <x_n> <y_n> <z_n>

		std::cin >> n_blocks_;
		if (n_blocks_ == 0)
			return false;

		assert(n_blocks_ <= 30);

		blocks_.resize(n_blocks_);
		for (auto& block : blocks_)
			std::cin >> block.size[0] >> block.size[1] >> block.size[2];
		
		return true;
	}

	virtual void solve(std::size_t i_case) override
	{
		/*********************************************************************
		mh(i, pos) is the maximum height of the tower that ends with the block
		(i) that is put such that its (pos) dimension, (pos) = 0, 1 or 2,
		is vertical.

		The recurrence relation is:
			mh(i, p) = height(i, p) + max {j, q : (i, p) > (j, q)} mh(j, q),
			where maximum is over all blocks j in the position q such that
			the block (i, p) can be placed on top of the block (j, q).
		
		Base case:
			mh(i, p) = height(i, p) if there are no blocks below (i, p).
		**********************************************************************/

		mh_.resize_and_fill(n_blocks_, 3, max_size);

		T height = 0;
		for (std::size_t i = 0; i < n_blocks_; ++i)
			for (unsigned int p = 0; p < 3; ++p)
				height = std::max(height, max_height(i, p));

 		std::cout << "Case " << i_case + 1 << ": maximum height = " << height << '\n';
	}

	T max_height(std::size_t i, unsigned int p)
	{
		auto& m = mh_(i, p);
		if (m != max_size)
			return m;

		m = blocks_[i].height(p);
		for (std::size_t j = 0; j < n_blocks_; ++j)
			for (unsigned int q = 0; q < 3; ++q)
				if (placeable(blocks_[i].base(p), blocks_[j].base(q)))
					m = std::max(m, max_height(j, q) + blocks_[i].height(p));

		return m;
	}

	static bool placeable(const Base& a, const Base& b)
	{
		return (a.x < b.x && a.y < b.y) || (a.x < b.y && a.y < b.x);
	}

private:
	std::size_t n_blocks_;
	std::vector<Block> blocks_;
	Matrix<T> mh_;
};

int main()
{
	Babylon p;
	return p.run();
}

/*********************************************************************
Optimal array multiplication sequence
-------------------------------------
UVa ID: 348

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "matrix.hpp"
#include <cassert>
#include <string>
#include <vector>

using Extent = unsigned int;
using Size = unsigned int;

class Optimal_mult_seq
{
public:
	Optimal_mult_seq(const std::vector<Extent>& extents)
	{
		const auto n_matrices = static_cast<Size>(extents.size() - 1);
		m_.resize(n_matrices, n_matrices);

		// Base case
		for (Size i = 0; i < n_matrices; ++i)
			m_(i, i).cost = 0;

		// Recurrences
		for (Size d = 1; d < n_matrices; ++d)
			for (Size i = 0; i < n_matrices - d; ++i)
			{
				const auto j = i + d;
				for (auto k = i; k < j; ++k)
				{
					// Cost of computing the outermost multiplication
					// in the expression(A_i ... A_k) (A_{k + 1} ... A_j)
					const Extent product_cost = extents[i] * extents[k + 1] * extents[j + 1];

					const Extent cost = m_(i, k).cost + m_(k + 1, j).cost + product_cost;
					if (cost < m_(i, j).cost)
						m_(i, j) = {cost, k};
				}
			}
	}

	std::string parenthesization() const
	{
		const auto n_matrices = m_.rows();
		return parenthesization(0, n_matrices - 1);
	}

private:
	struct Split_cost
	{
		Extent cost = static_cast<Extent>(-1);
		Size split_index;
	};

	std::string parenthesization(Size i, Size j) const
	{
		if (i == j)
			return "A" + std::to_string(i + 1);
		else
		{
			const auto k = m_(i, j).split_index;
			return '(' + parenthesization(i, k) + " x " + parenthesization(k + 1, j) + ')';
		}
	}

private:
	// m(i, j).cost is the minimum number of operations needed to compute the product(A_i ... A_j),
	// m(i, j).split_index is the index(k) at which the product (A_i ... A_k) (A_{k + 1} ... A_j)
	// is split in the optimal parenthesization
	Matrix<Split_cost, Size> m_;
};

class CP : public CP2
{
private:
	virtual bool read_input(std::istream& in) override
	{
		Size n_matrices_;
		in >> n_matrices_;
		if (n_matrices_ == 0)
			return false;

		assert(n_matrices_ <= 10);

		extents_.resize(n_matrices_ + 1);
		for (Size i = 0; i < n_matrices_; ++i)
		{
			Extent rows, cols;
			in >> rows >> cols;
			assert(rows > 0 && cols > 0);

			extents_[i] = rows;
			extents_[i + 1] = cols;
		}

		return true;
	}

	virtual void solve(std::ostream& out, std::size_t i_case) const override
	{
		Optimal_mult_seq seq(extents_);
		out << "Case " << i_case + 1 << ": " << seq.parenthesization() << '\n';
	}

private:
	std::vector<Extent> extents_;
};

int main()
{
	CP p;
	return p.run();
}

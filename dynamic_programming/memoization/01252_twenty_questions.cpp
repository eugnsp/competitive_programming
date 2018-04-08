/*********************************************************************
Twenty questions
----------------
UVa ID: 01 252

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "bit.hpp"
#include "io.hpp"
#include "matrix.hpp"
#include <algorithm>
#include <cassert>
#include <string>
#include <vector>

using Size = unsigned int;
using Mask = Size;

class Twenty_questions
{
private:
	static constexpr auto max_size = static_cast<Size>(-1);

public:
	Twenty_questions(Size n_features, const std::vector<Mask>& objects)
		: n_features_(n_features), objects_(objects)
	{
		const auto n_masks = nth_bit<Mask>(n_features_);
		mq_.resize(n_masks, n_masks);
	}

	Size min_n_questions() const
	{
		mq_.fill(max_size);

		const auto all_objects_mask = 0;
		return min_questions(all_objects_mask, all_objects_mask);
	}

private:
	Size min_questions(Mask questions, Mask answers) const
	{
		auto& m = mq_(questions, answers);
		if (m != max_size)
			return m;

		const auto n_objects = std::count_if(objects_.cbegin(),
			objects_.cend(), [&questions, &answers](Mask object)
			{
				return (object & questions) == answers;
			});

		if (n_objects <= 1)
			return (m = 0);

		for (Size i = 0; i < n_features_; ++i)
		{
			if (is_bit_set(questions, i))
				continue;

			const auto with_ith_question = with_bit_set(questions, i);
			const auto min_q = std::max(
				min_questions(with_ith_question, answers),
				min_questions(with_ith_question, with_bit_flipped(answers, i)));

			m = std::min(m, min_q + 1);
		}

		return m;
	}

private:
	const Size n_features_;
	const std::vector<Mask>& objects_;

	// mq(q_mask, a_mask) is the minimum number of questions by which
	// every object in the set determined by the masks is identifiable,
	// an (object) belongs to the set iff (q_mask) & (object) == (a_mask)
	mutable Matrix<Size> mq_;
};

class CP : public CP2
{

private:
	virtual bool read_input(std::istream& in) override
	{
		Size n_objects;
		in >> n_features_ >> n_objects;
		if (n_features_ == 0 && n_objects == 0)
			return false;

		assert(0 < n_features_ && n_features_ <= 11);
		assert(0 < n_objects && n_objects <= 128);

		read_vector<std::string>(in, n_objects, objects_,
			[](auto& str)
			{
				return string_to_mask<Mask>(str);
			});

		return true;
	}

	virtual void solve(std::ostream& out, unsigned int) const override
	{
		const Twenty_questions qs(n_features_, objects_);
		out << qs.min_n_questions() << '\n';
	}

private:
	Size n_features_;
	std::vector<Mask> objects_;
};

int main()
{
	CP p;
	return p.run();
}

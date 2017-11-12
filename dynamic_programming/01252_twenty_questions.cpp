/*********************************************************************
Twenty questions
----------------
UVa ID: 1252

Goal:	minimize the maximum number of questions by which
		every object in the set is identifiable.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include "bit_mask.hpp"
#include "matrix.hpp"
#include <cstddef>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

class Twenty_questions : public CP2
{
private:
	static constexpr auto max_size = static_cast<std::size_t>(-1);

private:
	virtual bool read_input(std::istream& in) override
	{
		// <number of features> <number of objects = n>
		// <object_1>
		// ...
		// <object_n>

		std::size_t n_objects;
		in >> n_features_ >> n_objects;
		if (n_features_ == 0 && n_objects == 0)
			return false;

		assert(0 < n_features_ && n_features_ <= 11);
		assert(0 < n_objects && n_objects <= 128);

		objects_.clear();
		objects_.reserve(n_objects);
		std::generate_n(std::back_inserter(objects_), n_objects, [this, &in]()
		{
			std::string object;
			in >> object;
			assert(object.length() == n_features_);

			return Bit_mask(object);
		});

		return true;
	}

	virtual void solve(std::ostream& out, std::size_t) override
	{
		/*********************************************************************
		mq(q_mask, a_mask) is the minimum number of questions by which
			every object in the set determined by the masks is identifiable,
			an (object) belongs to the set iff (q_mask) & (object) == (a_mask).

		The recurrence relation:
			mq(q, a) = 1 + min {i : !q[i]}
							[max{mq(q.set[i], a), mq(q.set[i], a.flip[i])}].
		
		The base case:
			mq(q, a) = 0, if the number of object in the set is <= 1.
		**********************************************************************/

		const auto n = Bit_mask(n_features_).size();
		mq_.resize_and_fill(n, n, max_size);

		const auto all_objects_mask = Bit_mask(n_features_);
		out << min_questions(all_objects_mask, all_objects_mask) << '\n';
	}

	std::size_t min_questions(const Bit_mask& questions, const Bit_mask& answers)
	{
		auto& m = mq_(questions, answers);
		if (m != max_size)
			return m;

		const auto n_objects = std::count_if(objects_.cbegin(), objects_.cend(),
			[&questions, &answers](auto& object)
		{
			return (object & questions) == answers;
		});

		if (n_objects <= 1)
			return (m = 0);

		for (unsigned int i = 0; i < n_features_; ++i)
		{
			if (questions[i])
				continue;

			const auto with_ith_question = questions.with_set(i);			
			const auto min_q = std::max(
				min_questions(with_ith_question, answers),
				min_questions(with_ith_question, answers.with_flipped(i)));

			m = std::min(m, min_q + 1);
		}

		return m;
	}

private:
	unsigned int n_features_;
	std::vector<Bit_mask> objects_;
	Matrix<std::size_t> mq_;
};

int main()
{
	Twenty_questions p;
	return p.run();
}

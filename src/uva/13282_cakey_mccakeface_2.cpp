/*********************************************************************
Cakey McCakeFace
----------------
UVa ID: 132 82

Cakey McCakeFaceCakey McCakeFace’s signature pastry, the Unknowable
Cake, is baked daily in their Paris facility. The make-or-break trick
fort his cake is the cooking time, which is a very well-kept secret.
Eve, the well-known spy, wants to steal this secret, and your job is
to help her. Cakes are cooked in a single huge oven that has exactly
one front and one back door. The uncooked cakes are inserted through
the front door. After the exact and very secret cooking time has
passed, the cakes exit the oven through the back door. Only one cake
can go through the front or back door at any given time. Eve has
secretly installed detectors at the front and back ofthe oven. They
record a signal every time a cake passes through the doors. A cake
will therefore trigger the entry detector at some time t when it goes
through the front door, and then trigger the exit detector at time
exactly t + cooking_time, when it goes through the back door (all
cakes at Cakey McCakeFace are always perfectly cooked). After a few
days, she receives two sets of timestamps (in ms) corresponding to
entry and exit detectors. Unfortunately, the detectors are faulty:
they are sometimes triggered when no cake has passed, or they may
fail to be triggered when a cake passes. Eve noticed that she could
make a good guess of the secret cooking_time by finding the time
difference that maximizes the number of correspondences of entry and
exit detection times. Help Eve compute this.

Input
-----
The input file contains several test cases, each of them as described
below.
	Line 1: the number N of times the entry detector was triggered.
	Line 2: the number M of times the exit detector was triggered.
	Line 3: the N integer timestamps at which the entry detector was
            triggered, sorted in ascending order, with no repetition,
			space-separated.
	Line 4: the M integer timestamps at which the exit detector was
			triggered, sorted in ascending order, with no repetition,
			space-separated.

Limits:
	1 <= N, M <= 2'000;
	each timestamp is between 0 and 1'000'000'000 (inclusive).

Output
------
For each test case, the output must follow the description below.
A single integer: your best guess of the secret cooking_time,
the (positive or zero) time difference that maximizes the number
of correspondences of entry and exit detection times. If multiple
such values exist, the smallest one should be returned.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include <vector>

template<typename T>
T duration_estimate(const std::vector<T>& sent_ts, const std::vector<T>& recv_ts)
{
	static_assert(std::is_unsigned_v<T>);

	constexpr std::size_t mask_size = 8 * sizeof(T);
	constexpr std::size_t lo_mask = mask_size / 2 + 2;
	static_assert(lo_mask < mask_size);
	constexpr std::size_t hi_mask = mask_size - lo_mask;

	std::vector<std::vector<T>> dur_buckets(1ul << hi_mask);
	for (const auto recv_t : recv_ts)
		for (const auto sent_t : sent_ts)
		{
			if (sent_t > recv_t)
				break;

			const auto dt = recv_t - sent_t;
			const auto dt_hi = dt >> lo_mask;
			const auto dt_lo = dt - (dt_hi << lo_mask);
			dur_buckets[dt_hi].push_back(dt_lo);
		}

	std::size_t max_cnt = 0;
	T min_dur = 0;

	std::vector<std::size_t> counter(1ul << lo_mask);
	for (std::size_t ib = 0; ib < (1ul << hi_mask); ++ib)
	{
		const auto dur_hi = ib << lo_mask;
		for (const auto dur_lo : dur_buckets[ib])
		{
			const auto cnt = ++counter[dur_lo];
			const auto dur = dur_hi + dur_lo;
			if (cnt > max_cnt || (cnt == max_cnt && dur < min_dur))
			{
				max_cnt = cnt;
				min_dur = dur;
			}
		}

		for (auto dur_bucket : dur_buckets[ib])
			counter[dur_bucket] = 0;
	}

	return min_dur;
}

using Time = std::uint32_t;

class CP : public CP2
{
private:
	virtual bool read_input() override
	{
		std::size_t n, m;
		if (!read(n, m))
			return false;

		sent_ts_.clear();
		read_vec(n, sent_ts_);

		recv_ts_.clear();
		read_vec(m, recv_ts_);

		return true;
	}

	virtual void solve(unsigned int) override
	{
		write_ln(duration_estimate(sent_ts_, recv_ts_));
	}

private:
	std::vector<Time> sent_ts_;
	std::vector<Time> recv_ts_;
};

MAIN

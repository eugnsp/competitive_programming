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
#include <algorithm>
#include <cstddef>
#include <map>
#include <vector>

template<typename T>
T duration_estimate(const std::vector<T>& sent_ts, const std::vector<T>& recv_ts)
{
	std::vector<T> durs;
	durs.reserve(sent_ts.size() * recv_ts.size() / 2);
	for (const auto recv_t : recv_ts)
		for (const auto sent_t : sent_ts)
		{
			if (sent_t > recv_t)
				break;

			durs.push_back(recv_t - sent_t);
		}

	if (durs.empty())
		return 0;
	if (durs.size() == 1)
		return durs.front();

	std::sort(durs.begin(), durs.end());
	auto min_dur = durs.front();

	std::size_t curr_cnt = 1, max_cnt = 1;

	auto it = durs.begin();
	for (auto prev_dur = *it++; it != durs.end(); prev_dur = *it++)
		if (*it == prev_dur)
		{
			if (++curr_cnt > max_cnt)
			{
				max_cnt = curr_cnt;
				min_dur = *it;
			}
		}
		else
			curr_cnt = 1;

	return min_dur;
}

using Time = unsigned long;

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

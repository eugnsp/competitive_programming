/*********************************************************************
Team queue
----------
UVa ID: 540

Goal:	simulate a team queue.

This file is covered by the LICENSE file in the root of this project.
**********************************************************************/

#include "base.hpp"
#include <cassert>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>

class Team_queue : public CP2
{
private:
	using T = unsigned int;
	using El_to_team_map = std::unordered_map<T, std::size_t>;
	static constexpr auto invalid_element = static_cast<T>(-1);

	enum class Command_type
	{
		ENQUEUE,
		DEQUEUE
	};

	struct Command
	{
		Command_type type;
		T arg = invalid_element;
	};

	class Queue
	{
	private:

	public:
		Queue(std::size_t n_teams, const El_to_team_map& el_to_team_map)
			: n_teams_(n_teams), el_to_team_map_(el_to_team_map)
		{ }

		void push(T value)
		{
			const auto team = el_to_team_map_.at(value);
			assert(team < n_teams_);

			for (auto& q : queues_)
				if (q.first == team)
				{
					q.second.push(value);
					return;
				}

			queues_.push_back({team, {}});
			queues_.back().second.push(value);
		}

		T pop()
		{
			for (auto it = queues_.begin(); it != queues_.end(); ++it)
				if (!it->second.empty())
				{
					auto value = it->second.front();
					it->second.pop();
					if (it->second.empty())
						queues_.erase(it);

					return value;
				}

			return invalid_element;
		}

	private:
		const std::size_t n_teams_;
		const El_to_team_map& el_to_team_map_;
		std::vector<std::pair<std::size_t, std::queue<T>>> queues_;
	};

private:
	virtual bool read_input(std::istream& in) override
	{
		// <number of teams = n>
		// <number of members in team (1) = m_1> <member_1> ... <member m_1>
		// ...
		// <number of members in team (n) = m_n> <member_1> ... <member m_n>
		// <ENQUEUE> <member> or <DEQUEUE>

		in >> n_teams_;
		if (n_teams_ == 0)
			return false;

		assert(n_teams_ <= 1000);

		teams_.resize(n_teams_);
		for (auto& team : teams_)
		{
			std::size_t n_elements;
			in >> n_elements;
			assert(n_elements <= 1000);

			team.resize(n_elements);
			for (auto& element : team)
				in >> element;
		}

		std::string command;
		T arg;

		commands_.clear();
		while ((in >> command) && command != "STOP")
			if (command == "ENQUEUE")
			{
				in >> arg;
				commands_.push_back({Command_type::ENQUEUE, arg});
			}
			else if (command == "DEQUEUE")
				commands_.push_back({Command_type::DEQUEUE});

		return true;
	}

	virtual void solve(std::ostream& out, std::size_t i_case) override
	{
		el_to_team_map_.clear();
		for (std::size_t i = 0; i < n_teams_; ++i)
		{
			const auto& team = teams_[i];
			for (auto element : team)
				el_to_team_map_.insert({element, i});
		}

		Queue q(n_teams_, el_to_team_map_);

		out << "Scenario #" << i_case + 1 << '\n';
		for (const auto& command : commands_)
		{
			switch (command.type)
			{
			case Command_type::ENQUEUE:
				q.push(command.arg);
				break;

			case Command_type::DEQUEUE:
				out << q.pop() << '\n';
			}
		}

		out << '\n';
	}

private:
	std::size_t n_teams_;
	std::vector<std::vector<T>> teams_;
	std::vector<Command> commands_;
	El_to_team_map el_to_team_map_;
};

int main()
{
	Team_queue p;
	return p.run();
}
#pragma once

#include"Goal.h"

namespace AI
{
	template<class AgentType>
	class GoalComposite : public Goal<AgentType>
	{
		public Status = Goal<AgentType>::Status;

		GoalComposite(AgentType& agent):
			Goal<AgentType>(agent)
		{
		}

		virtual ~GoalComposite()
		{
			RemoveALLSubgoals();
		}

	protected:
		template<calss GoalType>
		void AddSubgoal()
		{
			static_assert(std::is_base_of_v<Goal, GoalType>());
		}
		void RemoveALLSubgoals()
		{
			for (auto& goal : mSubgoals)
			{
				goal->Terminate();
			}
			mSubgoals.clear();
		}
		Status ProcessSubgoals()
		{
			while (!mSubgoals.empty())
			{
				auto& goal = mSubgoals.front();
				if (goal->mStatus != Status::Completed && goal->mStatus != Status::Failed)
				{
					break;
				}
				goal->Terminate(0;
				mSubgoals.pop_front();
			}

			if (!mSubgoals.empty())
			{
				Status status = mSubgoals.front()->Process();
				if (status == Status::Completed&&mSubgoals.size() >1)
				{
					return Status::Active;

				}
				return status;
			}
			return Status::Completed;
		}

		using Subgoals = std::list<std::unique_ptr<Goal<AgentType>>>;
		Subgoals mSubgoals;
	};
}
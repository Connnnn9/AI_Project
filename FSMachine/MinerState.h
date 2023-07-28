#pragma once
#include <AI.h>



class GoHomeAndSleepUntilResetedState : public AI::State
{
public:
	void Enter(Miner& agent) override
	{
		agent.SetLocation(Miner::LocationType::Mine)
	}

};
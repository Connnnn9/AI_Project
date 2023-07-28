#pragma once
#include <AI.h>

enum MinerState
{
	GoHomeAndSleepUntilReseted,
	EnterMinerAndDig,
	QuenchThirst,
	VisitBankAndDepositGold
};

class GoHomeAndSleepUntilResetedState : public AI::State
{
public:
	void Enter(Miner& agent) override
	{

	}

};
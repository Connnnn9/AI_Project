#pragma once

#include <AI.h>
#include "MinerState.h"

class Miner
{
public:
	enum LocationType
	{
		Home,
		Mine,
		Saloon,
		Bank
	};

	enum MinerState
	{
		GoHomeAndSleepUntilReseted,
		EnterMinerAndDig,
		QuenchThirst,
		VisitBankAndDepositGold
	};

	Miner(int ID);
	void update();
	void ChangeState(MinerState newState);
	//states
	LocationType GetlocationType();
	bool isThirsty() const;
	bool PocketsFull() const;
	bool wealthy() const;
	bool Rested() const;

	//functions
	void IncreaseFatique();
	void AddGoldCarrid(int amount);
	void AddGoldToBank(int amount);
	void IncreaseRest();

private:
	AI::StateMachine mStateMachine;
	LocationType mLocation;
	int m_iGoldCarried; // # of nuggets in miner’s pocket
	int m_iMoneyInBank; // Amount of money in bank
	int m_iThirst; // Higher value = thirstier miner
	int m_iFatigue; // Higher value = miner more tired

};


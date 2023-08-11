#pragma once

#include <AI.h>
#include "MinerState.h"

enum class MinerStates
{
	GoHomeAndSleepUntilRested,
	EnterMineAndDigForNugget,
	QuenchThirst,
	VisitBankAndDepositGold,
	Hungry,
	WantToPlayWithFriends,
	NeedToShop,
	SendGoodsToHome
};

class Miner
{
public:
	enum LocationType
	{
		Home,
		Mine,
		Saloon,
		Bank,
		FriendsPlace,
		ChinesefoodRestruant,
		Superstore
	};

	Miner() = default;
	void Initialize();
	void Terminate();
	void Update(float deltaTime);
	void ChangeState(MinerStates newState);

	//check states
	LocationType GetLocationType();
	bool IsThristy() const;
	bool PocketsFull() const;
	bool Wealthy() const;
	bool Rested() const;
	bool Full() const;
	bool GoodsIsEngough() const;
	bool isLonely() const;

	//action functions
	void SetLocation(LocationType location);
	void IncreaseFatigue();
	void AddGoldCarried(int amount);
	void AddGoldToBank(int amount);
	void AddGoodsToHome(int amount);
	void EatChinesefood();
	void ResetFatigue();
	void ResetReset();
	void Shopping(int amount);
	void DrivetoFriendsPlaceandPlay();

private:
	AI::StateMachine<Miner>* mStateMachine;
	LocationType m_Location;
	int m_iGoldCarried;
	int m_iGoodsCarried;
	int mMoneyInBank;
	int mThirst;
	int mEnergy;
	int mFatigue;
	int mGoods;
	int mLonelyness;

};
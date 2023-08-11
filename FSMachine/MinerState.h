#pragma once

#include <AI.h>
#include "Miner.h"
#include "ImGui/Inc/imgui.h"


class GoHomeAndSleepUntilRested : public AI::State<Miner>
{
public:
	virtual void Enter(Miner& agent) override
	{
		agent.SetLocation(Miner::LocationType::Home);
	}
	virtual void Update(Miner& agent, float deltaTime) override
	{
		agent.ResetReset();
	}
	virtual void Exit(Miner& agent) override
	{

	}
	virtual void Debug() override
	{
		ImGui::Text("Resting!");
	}
};

class EnterMineAndDigForNugget : public AI::State<Miner>
{
public:
	virtual void Enter(Miner& agent) override
	{
		agent.SetLocation(Miner::LocationType::Mine);
	}
	virtual void Update(Miner& agent, float deltaTime) override
	{
		agent.AddGoldCarried(1);
	}
	virtual void Exit(Miner& agent) override
	{

	}
	virtual void Debug() override
	{
		ImGui::Text("Hustling for money!");
	}
};

class QuenchThirst : public AI::State<Miner>
{
public:
	virtual void Enter(Miner& agent) override
	{
		agent.SetLocation(Miner::LocationType::Saloon);
	}
	virtual void Update(Miner& agent, float deltaTime) override
	{
		agent.ResetFatigue();
		if (!agent.IsThristy())
		{
			agent.ChangeState(MinerStates::EnterMineAndDigForNugget);
		}
	}
	virtual void Exit(Miner& agent) override
	{
		//nothing
	}
	virtual void Debug() override
	{
		ImGui::Text("Drinking");
	}
};

class VisitBankAndDepositGold : public AI::State<Miner>
{
public:
	virtual void Enter(Miner& agent) override
	{
		agent.SetLocation(Miner::LocationType::Bank);
	}
	virtual void Update(Miner& agent, float deltaTime) override
	{
		agent.AddGoldToBank(1);
		if (agent.Wealthy())
		{
			agent.ChangeState(MinerStates::GoHomeAndSleepUntilRested);
		}
		else
		{
			agent.ChangeState(MinerStates::VisitBankAndDepositGold);
		}

	}
	virtual void Exit(Miner& agent) override
	{

	}

	virtual void Debug() override
	{
		ImGui::Text("Depoisting golds!");
	}
};
// assignment part
class Hungry : public AI::State<Miner>
{
public:
	virtual void Enter(Miner& agent) override
	{
		agent.SetLocation(Miner::LocationType::ChinesefoodRestruant);
	}
	virtual void Update(Miner& agent, float deltaTime) override
	{
		agent.EatChinesefood();
		if (agent.Wealthy())
		{
			agent.ChangeState(MinerStates::GoHomeAndSleepUntilRested);
		}
		else
		{
			agent.ChangeState(MinerStates::VisitBankAndDepositGold);
		}

	}
	virtual void Exit(Miner& agent) override
	{

	}

	virtual void Debug() override
	{
		ImGui::Text("Depoisting golds!");
	}
};
// assignment part
class WantToPlayWithFriends : public AI::State<Miner>
{
public:
	virtual void Enter(Miner& agent) override
	{
		agent.SetLocation(Miner::LocationType::FriendsPlace);
	}
	virtual void Update(Miner& agent, float deltaTime) override
	{
		agent.DrivetoFriendsPlaceandPlay();
		if (agent.isLonely())
		{
			agent.ChangeState(MinerStates::WantToPlayWithFriends);
		}
		else
		{
			agent.ChangeState(MinerStates::GoHomeAndSleepUntilRested);
		}

	}
	virtual void Exit(Miner& agent) override
	{

	}

	virtual void Debug() override
	{
		ImGui::Text("Depoisting golds!");
	}
};
//assignment part
class NeedToShop : public AI::State<Miner>
{
public:
	virtual void Enter(Miner& agent) override
	{
		agent.SetLocation(Miner::LocationType::Superstore);
	}
	virtual void Update(Miner& agent, float deltaTime) override
	{
		agent.Shopping(10);
		if (agent.GoodsIsEngough())
		{
			agent.ChangeState(MinerStates::SendGoodsToHome);
		}
		else
		{
			agent.ChangeState(MinerStates::NeedToShop);
		}
	}
	virtual void Exit(Miner& agent) override
	{

	}

	virtual void Debug() override
	{
		ImGui::Text("Shopping now!");
	}
};
class SendGoodsToHome : public AI::State<Miner>
{
public:
	virtual void Enter(Miner& agent) override
	{
		agent.SetLocation(Miner::LocationType::Home);
	}
	virtual void Update(Miner& agent, float deltaTime) override
	{
		agent.AddGoodsToHome(10);
	}
	virtual void Exit(Miner& agent) override
	{

	}

	virtual void Debug() override
	{
		ImGui::Text("Goods is home now!");
	}
};

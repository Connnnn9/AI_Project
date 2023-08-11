#include "MinerState.h"

void Miner::Initialize()
{
	m_Location = LocationType::Home;
	m_iGoldCarried = 0;
	mMoneyInBank = 0;
	mThirst = 0;
	mFatigue = 0;
	mGoods = 10;
	mLonelyness = 0;
	mStateMachine = new AI::StateMachine<Miner>(*this);
	mStateMachine->AddState<GoHomeAndSleepUntilRested>();
	mStateMachine->AddState<EnterMineAndDigForNugget>();
	mStateMachine->AddState<QuenchThirst>();
	mStateMachine->AddState<VisitBankAndDepositGold>();
	mStateMachine->AddState<Hungry>();
	mStateMachine->AddState<WantToPlayWithFriends>();
	mStateMachine->AddState<NeedToShop>();
	mStateMachine->AddState<SendGoodsToHome>();
	mStateMachine->ChangeState(0);
}
void Miner::Terminate()
{
	delete mStateMachine;
	mStateMachine = nullptr;
}
void Miner::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
}
void Miner::ChangeState(MinerStates newState)
{
	mStateMachine->ChangeState((int)newState);
}

//check states
Miner::LocationType Miner::GetLocationType()
{
	return m_Location;
}
bool Miner::IsThristy() const
{
	return mThirst >= 4;
}
bool Miner::PocketsFull() const
{
	return m_iGoldCarried >= 10;
}
bool Miner::Wealthy() const
{
	return mMoneyInBank < 100;
}
bool Miner::Rested() const
{
	return true;
}
bool Miner::Full() const
{
	return mEnergy <= 5;
}

//action functions
void Miner::SetLocation(LocationType location)
{
	m_Location = location;
}
void Miner::IncreaseFatigue()
{
	mThirst++;
}
void Miner::AddGoldCarried(int amount)
{
	m_iGoldCarried += amount;
}
void Miner::AddGoldToBank(int amount)
{
	mMoneyInBank += m_iGoldCarried;
}
void Miner::EatChinesefood()
{
	mEnergy += 10;
}
void Miner::ResetFatigue()
{
	mThirst = 0;
}
void Miner::ResetReset()
{
}
void AddGoodsToHome(int amount)
{
}
void Shopping()
{
}
void DrivetoFriendsPlaceandPlay()
{
}
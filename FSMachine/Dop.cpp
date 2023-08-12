#include "DogState.h"

void Dog::Initialize()
{
	m_Location = LocationType::DogHome;
	mThirst=0;
	mSaitiety=100;
	mTiredness=0;
	mHappiness=100;
	mStateMachine = new AI::StateMachine<Dog>(*this);
	mStateMachine->AddState<GoDogHomeToRest>();
	mStateMachine->AddState<PlayWithOwner>();
	mStateMachine->AddState<WantToEat>();
	mStateMachine->AddState<GaurdTheHome>();
	mStateMachine->ChangeState(0);
}
void Dog::Terminate()
{
	delete mStateMachine;
	mStateMachine = nullptr;
}
void Dog::Update(float deltaTime)
{
	mStateMachine->Update(deltaTime);
}
void Dog::ChangeState(DogStates newState)
{
	mStateMachine->ChangeState((int)newState);
}

//check states
Dog::LocationType Dog::GetLocationType()
{
	return m_Location;
}

bool Dog::IsHungryOrThristy() const
{
	if (mSaitiety < 0 || mThirst>10)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Dog::IsTired() const
{
	if (mTiredness>100)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Dog::isLonely() const
{
	if (mHappiness<=0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


//action functions
void Dog::SetLocation(LocationType location)
{
	m_Location = location;
}

void Dog::EatAndDrink()
{
	mThirst -= 10;
	mSaitiety += 100;
}
void Dog::GuardMode()
{
	mThirst += 1;
	mSaitiety -= 10;
	mHappiness -= 10;
	mTiredness += 10;
}
void Dog::ResetReset()
{
	mTiredness = 0;
}void Dog::IncreaseHappiness()
{
	mHappiness += 90;
}

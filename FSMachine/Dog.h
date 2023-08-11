#pragma once

#include <AI.h>
#include "MinerState.h"

enum class DogStates
{
	GoDogHomeToRest,
	PlayWithOwner,
	WantToEat,
	GaurdTheHome
};

class Dog
{
public:
	enum LocationType
	{
		DogHome,
		DiningRoom,
		BackYard,
		FrontDoor
	};

	Dog() = default;
	void Initialize();
	void Terminate();
	void Update(float deltaTime);
	void ChangeState(DogStates newState);

	//check states
	LocationType GetLocationType();
	bool IsHungryOrThristy() const;
	bool IsTired() const;
	bool isLonely() const;


	//action functions
	void SetLocation(LocationType location);
	void EatAndDrink();
	void ResetReset();
	void GuardMode();
	void IncreaseHappiness();

private:
	AI::StateMachine<Dog>* mStateMachine;
	LocationType m_Location;
	int mThirst;
	int mSaitiety;
	int mTiredness;
	int mHappiness;


};
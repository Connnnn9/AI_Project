#pragma once

#include <AI.h>
#include "Dog.h"
#include "ImGui/Inc/imgui.h"


class GoDogHomeToRest : public AI::State<Dog>
{
public:
	virtual void Enter(Dog& agent) override
	{
		agent.SetLocation(Dog::LocationType::DogHome);
	}
	virtual void Update(Dog& agent, float deltaTime) override
	{
		if (agent.IsTired())
		{
		agent.ResetReset();
		}
		if (!agent.IsTired())
		{
			agent.ChangeState(DogStates::GaurdTheHome);
		}
	}
	virtual void Exit(Dog& agent) override
	{

	}
	virtual void Debug() override
	{
		ImGui::Text("Resting!");
	}
};

class PlayWithOwner : public AI::State<Dog>
{
public:
	virtual void Enter(Dog& agent) override
	{
		agent.SetLocation(Dog::LocationType::BackYard);
	}
	virtual void Update(Dog& agent, float deltaTime) override
	{
		agent.IncreaseHappiness();
	}
	virtual void Exit(Dog& agent) override
	{

	}
	virtual void Debug() override
	{
		ImGui::Text("Playing!");
	}
};

class WantToEat : public AI::State<Dog>
{
public:
	virtual void Enter(Dog& agent) override
	{
		agent.SetLocation(Dog::LocationType::DiningRoom);
	}
	virtual void Update(Dog& agent, float deltaTime) override
	{
		agent.EatAndDrink();
		if (!agent.IsHungryOrThristy())
		{
			agent.ChangeState(DogStates::GaurdTheHome);
		}
	}
	virtual void Exit(Dog& agent) override
	{
		//nothing
	}
	virtual void Debug() override
	{
		ImGui::Text("Drinking And Eating");
	}
};

class GaurdTheHome : public AI::State<Dog>
{
public:
	virtual void Enter(Dog& agent) override
	{
		agent.SetLocation(Dog::LocationType::FrontDoor);
	}
	virtual void Update(Dog& agent, float deltaTime) override
	{
		agent.GuardMode();
		if (agent.IsHungryOrThristy())
		{
			agent.ChangeState(DogStates::WantToEat);
		}
		else if (agent.IsTired())
		{
			agent.ChangeState(DogStates::PlayWithOwner);
		}

	}
	virtual void Exit(Dog& agent) override
	{

	}

	virtual void Debug() override
	{
		ImGui::Text("Guarding!");
	}
};

#pragma once

#include"SteeringBehavior.h"

namespace AI
{
	class SeekBehavior: public SteeringBehavior
	{
	public:
	virtual X::Math::Vector2 Calculate(Agent& agent) override;
	};
	class FleeBehavior: public SteeringBehavior
	{
	public:
	virtual X::Math::Vector2 Calculate(Agent& agent) override;
		
	};
}
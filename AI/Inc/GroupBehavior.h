#pragma once


#include "SteeringBehavior.h"

namespace AI
{
	class Agent;

	class SeparationBehaviour : public SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent);
	};

	class AlignmentBehavior : public SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent);
	};

	class CohesionBehavior : public SteeringBehavior
	{
	public:
		X::Math::Vector2 Calculate(Agent& agent);
	};


}
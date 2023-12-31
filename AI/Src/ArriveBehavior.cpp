#include "Precomplied.h"
#include "ArriveBehavior.h"
#include "Agent.h"

using namespace AI;
extern ArriveBehavior::Deceleration deceleration;
X::Math::Vector2 AI::ArriveBehavior::Calculate(Agent& agent)
{
	const auto agentToDest = agent.destination - agent.position;
	const float distToDest = X::Math::Magnitude(agentToDest);
	float speed = 0.0f;
	if (distToDest >1.0f)
	{
		const float decelTweaker = agent.mass * 1.5f;
		speed = distToDest / (((float)deceleration + 1.0f) * decelTweaker);
		speed = X::Math::Min(speed, agent.maxSpeed);
	}

	const auto desiredVelocity = (agentToDest / distToDest) * speed;
	const auto arriveForce = desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		X::DrawScreenLine(agent.position, agent.position + desiredVelocity, X::Colors::Red);
		X::DrawScreenLine(agent.position, agent.position + agent.velocity, X::Colors::Green);
		X::DrawScreenCircle(agent.destination, 20.0f, X::Colors::Aqua);
	}
	return arriveForce;
}

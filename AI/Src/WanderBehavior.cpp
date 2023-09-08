#include "Precomplied.h"
#include "WanderBehavior.h"
#include "Agent.h"

using namespace AI;

X::Math::Vector2 WanderBehavior::Calculate(Agent& agent)
{
	auto newWanderTarget = mLocalWnaderTarget + (X::RandomUnitCircle()* mWanderJitter);
	
	newWanderTarget = X::Math::Normalize(newWanderTarget) * mWanderWanderRadius;
	mLocalWnaderTarget = newWanderTarget;

	newWanderTarget += X::Math::Vector2(0.0f, mWanderDistance);
	const auto worldTransform = agent.GetWorldTransform();
	const auto worldWanderTarget = X::Math::TransformCoord(newWanderTarget, worldTransform);
	

	const auto agentDist = worldWanderTarget - agent.position;
	const float disToDest = X::Math::Magnitude(agentDist);
	if (disToDest<=0.01f)
	{
		return X::Math::Vector2::Zero();
	}

	const auto desiredVelocity = (agentDist / disToDest) * agent.maxSpeed;
	const auto seekForce = desiredVelocity - agent.velocity;

	if (IsDebug())
	{
		const auto WanderCenter = X::Math::TransformCoord({ 0.0f, mWanderDistance
			}, worldTransform);
		X::DrawScreenCircle(WanderCenter, mWanderWanderRadius, X::Colors::Yellow);
		X::DrawScreenDiamond(worldWanderTarget, 3.0f, X::Colors::Red);
		X::DrawScreenLine(agent.position,worldWanderTarget,X::Colors::Gray);
	}

	return seekForce;
}

void WanderBehavior::Setup(float radius, float distance, float jitter)
{
	mWanderWanderRadius = radius;
	mWanderDistance = distance;
	mWanderJitter = jitter;
}
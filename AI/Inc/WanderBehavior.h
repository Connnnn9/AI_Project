#include"SteeringBehavior.h"
namespace AI
{
	class WanderBehavior :public SteeringBehavior
	{
	public:
		virtual X::Math::Vector2 Calculate(Agent& agent) = 0;
		void Setup(float radius, float distance, float jitter);

	private:
		X::Math::Vector2 mLocalWnaderTarget = X::Math::Vector2::Zero();
		float mWanderWanderRadius = 1.0f;
		float mWanderDistance = 0.0f;
		float mWanderJitter = 0.1f;
	};
}
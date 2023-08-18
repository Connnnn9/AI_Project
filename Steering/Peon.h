#pragma once

#include<AI.h>

class  Peon: public AI::Agent
{
public:
	Peon(AI::AIWorld& world);

	void Load();
	void Unload();
	void Update(float deltaTime);
	void Render();
	void ShowDebug(bool dbug);
	void SetFlee(bool active) { mFleeBehavior->SetActive(active); }

private:

	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	AI::SeekBehavior* mSeekBehavior = nullptr;
	AI::SeekBehavior* mFleeBehavior = nullptr;
	AI::WanderBehavior* mWanderBehavior = nullptr;
	std::array<X::TextureId, 16> mTextureIDs;
};


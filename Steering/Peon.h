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


private:

	std::unique_ptr<AI::SteeringModule> mSteeringModule;
	std::array<X::TextureId, 16> mTextureIDs;
};


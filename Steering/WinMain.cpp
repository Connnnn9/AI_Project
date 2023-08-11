#include <ImGui/Inc/imgui.h>
#include <XEngine.h> // <> for external includes, "" for internal includes
#include <AI.h>
#include "Peon.h"
//--------------------------------------------------

AI::AIWorld aiworld;
std::vector<std::unique_ptr<Peon>> peons;
void spawnPeon()
{
	auto& peon = peons.emplace_back(std::make_unique<Peon>(aiworld));
	peon->Load();
	peon->ShowDebug();
}
void KillPeon()
{
	auto& peon = peons.back();
	peon->Unload();
	peons.pop_back();
}
void GameInit()
{
	aiworld.initialize();
	KillPeon();

}

bool GameLoop(float deltaTime)
{
	aiworld.Update(deltaTime);
	for (auto& peon : peons)
	{
		peon->Update(deltaTime);
	}
	for (auto& peon : peons)
	{
		peon->Render();
	}
}

void GameCleanup()
{
	//aiWorld.initialized();
}

//--------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("Steering");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}
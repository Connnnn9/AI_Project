#include <ImGui/Inc/imgui.h>
#include <XEngine.h> // <> for external includes, "" for internal includes
#include <AI.h>
#include "Peon.h"
//--------------------------------------------------

AI::AIWorld aiworld;
std::vector<std::unique_ptr<Peon>> peons;
bool showDebug = false;
float wanderJitter = 5.0f;
float wanderRadius = 20.0f;
float wanderDistance = 50.0f;

AI::ArriveBehavior::Deceleration deceleration = AI::ArriveBehavior::Deceleration::Normal;
void spawnPeon()
{
	auto& peon = peons.emplace_back(std::make_unique<Peon>(aiworld));
	peon->Load();
	peon->ShowDebug(showDebug);

	const float halfScreenWidth= X::GetScreenWidth() * 0.5f;
	const float halfScreenHeight=X::GetScreenHeight() * 0.5f;
	peon->position = X::RandomVector2({ 100.0f,100.0f }, { halfScreenWidth - 100.0f,halfScreenHeight - 100.0f});
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
	ImGui::Begin("Steering Controls", nullptr, ImGuiWindowFlags_AlwaysAutoResize);
	if (ImGui::Button("Spawn"))
	{
		spawnPeon();
	}
	if (ImGui::Button("Kill"))
	{
		KillPeon();
	}
	if (ImGui::CollapsingHeader("Wander##Settings", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Jitter##", &wanderJitter, 0.1f, 0.1f, 10.0f);
	}
	if (ImGui::CollapsingHeader("Wander##Settings", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Distance##", &wanderJitter, 0.1f, 0.1f, 10.0f);
	}
	if (ImGui::CollapsingHeader("Wander##Settings", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Radius##", &wanderJitter, 0.1f, 0.1f, 10.0f);
	}
	
	ImGui::End();

	if (X::IsMousePressed(X::Mouse::LBUTTON))
	{
		const auto mouseX = static_cast<float>(X::GetMouseScreenX());
		const auto mouseY = static_cast<float>(X::GetMouseScreenY());
		const auto destination = X::Math::Vector2(mouseX, mouseY);
		for (auto& peon ：peons)
		{

		}
	}
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
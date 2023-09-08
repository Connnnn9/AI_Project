#include <ImGui/Inc/imgui.h>
#include <XEngine.h> // <> for external includes, "" for internal includes
#include <AI.h>
#include "Peon.h"
#include "Typesid.h"
//--------------------------------------------------

AI::AIWorld aiworld;
std::vector<std::unique_ptr<Peon>> peons;


bool showDebug = false;
float wanderJitter = 5.0f;
float wanderRadius = 20.0f;
float wanderDistance = 50.0f;

//AI::ArriveBehavior::Deceleration deceleration = AI::ArriveBehavior::Deceleration::Normal;
int activeBehavior = 0;

void spawnPeon()
{
	auto& peon = peons.emplace_back(std::make_unique<Peon>(aiworld));
	peon->Load();
	peon->ShowDebug(showDebug);
	//peon->target = &targetPeon;

	const float ScreenWidth = X::GetScreenWidth() ;
	const float ScreenHeight = X::GetScreenHeight();
	peon->position = X::RandomVector2({ 100.0f,100.0f }, { ScreenWidth - 100.0f,ScreenHeight - 100.0f });
}
void KillPeon()
{
	auto& peon = peons.back();
	peon->Unload();
	peons.pop_back();
}
void GameInit()
{
	aiworld.Initialize();
	//targetPeon.SetFlee(true);
	//targetPeon.SetFlee(true);
	//targetPeon.SetFlee(true);
	spawnPeon();

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
	if (ImGui::Checkbox("showDebug", &showDebug))
	{
		for (auto& peon : peons)
		{
			peon->ShowDebug(showDebug);
		}
	}
	static const char* behaviors[] =
	{
		"Seek",
		"Wander",
	};
	if (ImGui::Combo("ActiveBehavior##", &activeBehavior, behaviors, std::size(behaviors)))
	{
		for (auto& peon : peons)
		{
			//peon->SetFlee(activeBehavior == 0);
			peon->SetSeek(activeBehavior == 0);
			peon->SetWander(activeBehavior == 1);
			//peon->SetArrive(activeBehavior == 3);
		}
	}
	if (ImGui::CollapsingHeader("Wander##Settings", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::DragFloat("Jitter##", &wanderJitter, 0.1f, 0.1f, 10.0f);
		ImGui::DragFloat("Raidus##", &wanderRadius, 0.1f, 0.1f, 100.0f);
		ImGui::DragFloat("Distance##", &wanderDistance, 0.1f, 0.1f, 500.0f);
	}
	/*if (ImGui::CollapsingHeader("Arrive##Settings", ImGuiTreeNodeFlags_DefaultOpen))
	{
		static const char* decelerationSpeeds[] =
		{
			"Fast"
			,"Normal"
			,"Slow"
		};
		int decel = static_cast<int>(deceleration);
		if (ImGui::Combo("Decleration##", &decel, decelerationSpeeds, std::size(decelerationSpeeds)))
		{
			deceleration = static_cast<AI::ArriveBehavior::Deceleration>(decel);
		}
	}*/
	ImGui::End();

	aiworld.Update();
	//if (X::IsMousePressed(X::Mouse::LBUTTON))
	//{
	//	const auto mouseX = static_cast<float>(X::GetMouseScreenX());
	//	const auto mouseY = static_cast<float>(X::GetMouseScreenY());
	//	const auto destination = X::Math::Vector2(mouseX, mouseY);
	//	for (auto& peon : peons)
	//	{
	//		peon->destination = destination;
	//	}
	//}
	//aiworld.Update();
	//for (auto& peon : peons)
	//{
	//	auto neighbors = aiworld.GetEntitiesInRange({ peon->position,100.0f }, Types::PeonID);
	//	peon->neighbors.clear();
	//	for (auto& n : neighbors)
	//	{
	//		if (n != peon.get())
	//		{
	//			peon->neighbors.push_back(static_cast<AI::Agent*>(n));
	//		}
	//	}
	//}
	//targetPeon.Update(deltaTime);
	
	for (auto& peon : peons)
	{
		peon->Update(deltaTime);
	}
	//targetPeon.Render();
	for (auto& peon : peons)
	{
		peon->Render();
	}
	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{
	//targetPeon.Unload();
	for (auto& peon : peons)
	{
		peon->Unload();
	}
	//aiWorld.initialized();
}

//--------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("Perception");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}
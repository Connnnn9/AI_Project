#include "TileMap.h"
#include <ImGui/Inc/imgui.h>
#include <XEngine.h> // <> for external includes, "" for internal includes

Path path;
TileMap tileMap;
X::TextureId textureId;
X::Math::Vector2 position;

int StartX = 0;
int StartY = 0;
int EndX = 0;
int EndY = 0;
//--------------------------------------------------

void GameInit()
{
	tileMap.LoadTiles("tiles.txt");
	tileMap.LoadMap("map.txt");
}

bool GameLoop(float deltaTime)
{
	ImGui::Begin("PathFinding");
	ImGui::DragInt("StartX##", &StartX, 1, 0, tileMap.GetColumns() - 1);
	ImGui::DragInt("StartY##", &StartY, 1, 0, tileMap.GetRows() - 1);
	ImGui::DragInt("EndX##", &EndX, 1, 0, tileMap.GetColumns() - 1);
	ImGui::DragInt("EndY##", &EndY, 1, 0, tileMap.GetRows() - 1);
	if (ImGui::Button("RunBFS##"))
	{
	
		path = tileMap.FindPathBFS(StartX, StartY, EndX, EndY);
	}
	ImGui::End();
	tileMap.Render();

	for (int i = 1; i < path.size(); ++i)
	{
		X::DrawScreenLine(path[i - 1], path[i], X::Colors::Red);
	}
	X::DrawScreenCircle(tileMap.GetPixelPosition(StartX,StartY),3,X::Colors::Azure);
	X::DrawScreenCircle(tileMap.GetPixelPosition(EndX, EndY), 3, X::Colors::Cyan);

	const bool quit = X::IsKeyPressed(X::Keys::ESCAPE);
	return quit;
}

void GameCleanup()
{

}

//--------------------------------------------------

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	X::Start("Pathfinding");
	GameInit();

	X::Run(GameLoop);

	GameCleanup();
	X::Stop();
	return 0;
}
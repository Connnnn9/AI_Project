#include"Precomplied.h"
#include"AIWorld.h"

using namespace AI;

namespace
{
	const float sCellSize = 100.0f;
}

void AI::AIWorld::Initialize(const X::Math::Vector2 & worldSize)
{
	const auto numColumns = static_cast<uint32_t>(std::ceilf(worldSize.x / sCellSize));
	const auto numRows = static_cast<uint32_t>(std::ceilf(worldSize.y / sCellSize));
	mGrid.Initialize(numColumns, numRows);
}

void AI::AIWorld::Update()
{
	mGrid.ClearCells();
	for (auto entity : mEntities)
	{
		const auto column = static_cast<uint32_t>(entity->position.x / sCellSize);
		const auto row = static_cast<uint32_t>(entity->position.y / sCellSize);
		mGrid.GetCell(column, row).push_back(entity);
	}
}

void AIWorld::RegisterEntity(Entity*entity)
{
	mEntities.push_back(entity);
}

void AIWorld::UnregisterEntity(Entity*entity)
{
	auto iter = std::find(mEntities.begin(), mEntities.end(), entity);
	if (iter != mEntities.end())
	{
		std::iter_swap(iter, mEntities.end() - 1);
		mEntities.pop_back();
	}
}

Agents AI::AIWorld::GetNeighborhood(const X::Math::Circle & range, uint16_t typeId)
{
	Agents agents;

	int minX = static_cast<int>((range.center.x - range.radius) / sCellSize);
	int maxX = static_cast<int>((range.center.x + range.radius) / sCellSize);
	int minY = static_cast<int>((range.center.y - range.radius) / sCellSize);
	int maxY = static_cast<int>((range.center.y + range.radius) / sCellSize);

	minX = X::Math::Max(minX, 0);
	maxX = X::Math::Min(maxX, (int)mGrid.GetColumns() - 1);
	minY = X::Math::Max(minY, 0);
	maxY = X::Math::Min(maxY, (int)mGrid.GetRows() - 1);

	for (int y = minY; y <= maxY; ++y)
	{
		for (int x = minX; x <= maxX; ++x)
		{
			auto& cell = mGrid.GetCell(x, y);
			for (auto entity : cell)
			{
				if (GetType(entity->id) == typeId)
				{
					agents.push_back(static_cast<Agent*>(entity));
				}
			}
		}
	}

	return agents;
}

Entities AI::AIWorld::GetEntities(const X::Math::Circle & range, uint16_t typeId)
{
	Entities entities;

	int minX = static_cast<int>((range.center.x - range.radius) / sCellSize);
	int maxX = static_cast<int>((range.center.x + range.radius) / sCellSize);
	int minY = static_cast<int>((range.center.y - range.radius) / sCellSize);
	int maxY = static_cast<int>((range.center.y + range.radius) / sCellSize);

	minX = X::Math::Max(minX, 0);
	maxX = X::Math::Min(maxX, (int)mGrid.GetColumns() - 1);
	minY = X::Math::Max(minY, 0);
	maxY = X::Math::Min(maxY, (int)mGrid.GetRows() - 1);

	for (int y = minY; y <= maxY; ++y)
	{
		for (int x = minX; x <= maxX; ++x)
		{
			auto& cell = mGrid.GetCell(x, y);
			for (auto entity : cell)
			{
				if (GetType(entity->id) == typeId)
					entities.push_back(entity);
			}
		}
	}

	return entities;
}

int AIWorld::GetNextId(uint16_t typeId)
{
	//42 = 32 + 8 + 2 = 00000000 00000000 00000000 00101010
	//42 << 16        = 00000000 00101010 <----------

	XASSERT(mNextId < UINT16_MAX, "RUN OUT OF IDS!");
	const int id = (typeId << 16) | mNextId++;
	return id;
}

uint16_t AIWorld::GetType(int id) const
{
	return static_cast<uint16_t>(id >> 16);
}
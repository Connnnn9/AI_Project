#include"Precomplied.h"
#include"AIWorld.h"

using namespace AI;

//namespace
//{
//	const float sCellSize = 100.0f;
//}

void AIWorld::Initialize()
{
}

void AIWorld::Update()
{
	
}

void AIWorld::Register(Entity* entity)
{
	XASSERT(std::find(mEntities.begin(), mEntities.end(), entity) == mEntities.end(), "AIWorld: entity already has ");
	mEntities.push_back(entity);
}

void AIWorld::Unregister(Entity*entity)
{
	auto iter = std::find(mEntities.begin(), mEntities.end(), entity);
	if (iter != mEntities.end())
	{
		mEntities.erase(iter);
	}
}

//Agents AI::AIWorld::GetNeighborhood(const X::Math::Circle & range, uint16_t typeId)
//{
//	Agents agents;
//
//	int minX = static_cast<int>((range.center.x - range.radius) / sCellSize);
//	int maxX = static_cast<int>((range.center.x + range.radius) / sCellSize);
//	int minY = static_cast<int>((range.center.y - range.radius) / sCellSize);
//	int maxY = static_cast<int>((range.center.y + range.radius) / sCellSize);
//
//	minX = X::Math::Max(minX, 0);
//	//maxX = X::Math::Min(maxX, (int)mGrid.GetColumns() - 1);
//	minY = X::Math::Max(minY, 0);
//	//maxY = X::Math::Min(maxY, (int)mGrid.GetRows() - 1);
//
//	for (int y = minY; y <= maxY; ++y)
//	{
//		for (int x = minX; x <= maxX; ++x)
//		{
//			auto& cell = mGrid.GetCell(x, y);
//			for (auto entity : cell)
//			{
//				if (GetType(entity->id) == typeId)
//				{
//					agents.push_back(static_cast<Agent*>(entity));
//				}
//			}
//		}
//	}
//
//	return agents;
//}

EntityPtr AIWorld::GetEntitiesInRange(const X::Math::Circle & range, uint32_t typeId)
{
	float radiusSq = range.radius * range.radius;
	EntityPtr entities;
	for (auto& entity : mEntities)
	{
		if (typeId == 0 || entity->GetTypeId() == typeId)
		{
			auto distVec = entity->position - range.center;
			if (X::Math::MagnitudeSqr(distVec)<= radiusSq)
			{
				entities.push_back(entity);
			}
		}

		return entities;
	}
	//Entities entities;
	//
	//int minX = static_cast<int>((range.center.x - range.radius) / sCellSize);
	//int maxX = static_cast<int>((range.center.x + range.radius) / sCellSize);
	//int minY = static_cast<int>((range.center.y - range.radius) / sCellSize);
	//int maxY = static_cast<int>((range.center.y + range.radius) / sCellSize);
	//
	//minX = X::Math::Max(minX, 0);
	//maxX = X::Math::Min(maxX, (int)mGrid.GetColumns() - 1);
	//minY = X::Math::Max(minY, 0);
	//maxY = X::Math::Min(maxY, (int)mGrid.GetRows() - 1);
	//
	//for (int y = minY; y <= maxY; ++y)
	//{
	//	for (int x = minX; x <= maxX; ++x)
	//	{
	//		auto& cell = mGrid.GetCell(x, y);
	//		for (auto entity : cell)
	//		{
	//			if (GetType(entity->id) == typeId)
	//				entities.push_back(entity);
	//		}
	//	}
	//}
	//
	//return entities;
}

//int AIWorld::GetNextId(uint16_t typeId)
//{
//	//42 = 32 + 8 + 2 = 00000000 00000000 00000000 00101010
//	//42 << 16        = 00000000 00101010 <----------
//
//	XASSERT(mNextId < UINT16_MAX, "RUN OUT OF IDS!");
//	const int id = (typeId << 16) | mNextId++;
//	return id;
//}
//
//uint16_t AIWorld::GetType(int id) const
//{
//	return static_cast<uint16_t>(id >> 16);
//}
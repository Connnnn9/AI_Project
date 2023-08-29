#pragma once

#include "Entity.h"
//#include "Agent.h"
//#include "PartitionGrid.h"

namespace AI
{
	class AIWorld
	{
	public:
		void Initialize();
		void Update();

		void Register(Entity*entity);
		void Unregister(Entity*entity);
		
		EntityPtr GetEntities() const { return mEntities; }
		
		EntityPtr GetEntitiesInRange(const X::Math::Circle& range, uint32_t typeId);

		uint32_t GetNextId() const
		{
			XASSERT(mNextId < UINT32_MAX, "AIWorld: run out Ids");
			return mNextId++;
		}

		
		//void AddObstacle(const X::Math::Circle& obstacle) { mObstacles.push_back(obstacle); }
		//void AddWall(const X::Math::LineSegment& wall) { mWalls.push_back(wall); }
		//
		//Agents GetNeighborhood(const X::Math::Circle& range, uint16_t typeId);
		//Entities GetEntities(const X::Math::Circle& range, uint16_t typeId);
		//
		//int GetNextId(uint16_t typeId);
		//uint16_t GetType(int id) const;

	private:
		mutable uint32_t mNextId = 0;
		EntityPtr mEntities;

		//Entities mEntities;
		//Obstacles mObstacles;
		//Walls mWalls;
		////AI::PartitionGrid::PartitionGrid<Entity> mGrid;
		//int mNextId = 0;
	};
}
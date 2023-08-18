#include"Precomplied.h"
#include "Entity.h"
using namespace AI;
Entity::Entity(AIWorld& world, uint16_t typeId)
{

}
AI::Entity::~Entity()
{
	world.Unregister(this);
}
Entity::GetTypeId()
{
}

X::Math::Matrix3 Entity::GetWorldTransform()
{
	const auto h = heading;
	const auto s = X::Math::PerpendicularRH(h);
	const auto d = position;

	return{ s.x,s.y,0.0,
			h.x,h.y,0.0,
			d.x,d.y,1.0f };
}
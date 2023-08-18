#pragma once
namespace AI
{
	class AIWorld;

	class  Entity
	{
	public:
		Entity(AIWorld& world, uint16_t typeId);
		virtual ~Entity();

		Entity(const Entity&) = delete;
		Entity(const Entity&&) = delete;
		Entity& operator=(const Entity&) = delete;
		Entity& operator=(const Entity&&) = delete;

		X::Math::Matrix3 GetWorldTransform() const;
		AIWorld& world;
		X::Math::Vector2 position = X::Math::Vector2::Zero();
		X::Math::Vector2 heading = X::Math::Vector2::YAxis();
		const int id = 0;
		float radius = 1.0f;
		uint32_t GetTypeId() const { return static_cast<uint32_t>(mUnqueId >> 32); }
		uint64_t GetUniqueId() const { return  mUnqueId; }
	private:
		const uint64_t mUnqueId = 0;
	};

	//using Entities = std::vector<Entity*>;
}
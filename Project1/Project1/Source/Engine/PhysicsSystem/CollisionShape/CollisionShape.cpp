#include "CollisionShape.h"
namespace Engine
{
	namespace PhysicsSystem
	{
		CollisionShape::CollisionShape()
			: m_shape(nullptr)
		{
		}

		CollisionShape::~CollisionShape()
		{
			delete m_shape;
		}
	}
}
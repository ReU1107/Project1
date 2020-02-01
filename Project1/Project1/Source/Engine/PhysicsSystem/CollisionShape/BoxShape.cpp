#include "BoxShape.h"
#include "../../Math/Vector3.h"
#include "btBulletCollisionCommon.h"
#include "btBulletDynamicsCommon.h"

namespace Engine
{
	namespace PhysicsSystem
	{
		BoxShape::BoxShape()
		{
		}

		BoxShape::~BoxShape()
		{
		}

		BoxShape::BoxShapePtr BoxShape::Create(const Vector3& halfExtents)
		{
			//btVector3 vec;
			//vec.setX(halfExtents.x);
			//vec.setY(halfExtents.y);
			//vec.setZ(halfExtents.z);

			auto box = std::make_shared<BoxShape>();
			//box->m_shape = new btBoxShape(vec);

			return box;
		}
	}
}
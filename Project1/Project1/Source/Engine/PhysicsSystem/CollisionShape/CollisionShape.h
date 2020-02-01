#pragma once
#include "btBulletCollisionCommon.h"

namespace Engine
{
	namespace PhysicsSystem
	{
		class CollisionShape
		{
		protected:
			btCollisionShape* m_shape;

		public:
			// コンストラクタ
			CollisionShape();
			// デストラクタ
			virtual ~CollisionShape();

		};

	}
}
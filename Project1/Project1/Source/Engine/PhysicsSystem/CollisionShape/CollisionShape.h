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
			// �R���X�g���N�^
			CollisionShape();
			// �f�X�g���N�^
			virtual ~CollisionShape();

		};

	}
}
#pragma once
#include "CollisionShape.h"

namespace Engine
{
	namespace PhysicsSystem
	{
		class CapsuleShape final : public CollisionShape
		{
		private:
			using base = CollisionShape;

		public:
			// �R���X�g���N�^
			CapsuleShape();
			// �f�X�g���N�^
			virtual ~CapsuleShape();

		};
	}
}
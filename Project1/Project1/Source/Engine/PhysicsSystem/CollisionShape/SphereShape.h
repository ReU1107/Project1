#pragma once
#include "CollisionShape.h"

namespace Engine
{
	namespace PhysicsSystem
	{
		class SphereShape final : public CollisionShape
		{
		private:
			using base = CollisionShape;
			using SphereShapePtr = std::shared_ptr<SphereShape>;
		public:
			// �R���X�g���N�^
			SphereShape();
			// �f�X�g���N�^
			virtual ~SphereShape();

		public:
			static SphereShapePtr Create(float radius);

		};
	}
}
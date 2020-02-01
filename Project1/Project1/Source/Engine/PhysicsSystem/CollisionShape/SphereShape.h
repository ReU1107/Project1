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
			// コンストラクタ
			SphereShape();
			// デストラクタ
			virtual ~SphereShape();

		public:
			static SphereShapePtr Create(float radius);

		};
	}
}
#pragma once
#include "CollisionShape.h"

namespace Engine
{
	struct Vector3;

	namespace PhysicsSystem
	{
		class BoxShape final : public CollisionShape
		{
		private:
			using base = CollisionShape;
			using BoxShapePtr = std::shared_ptr<BoxShape>;

		public:
			// 
			BoxShape();
			// 
			virtual ~BoxShape();

			static BoxShapePtr Create(const Vector3& halfExtents);

		};

	}
}
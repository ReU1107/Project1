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
			// コンストラクタ
			CapsuleShape();
			// デストラクタ
			virtual ~CapsuleShape();

		};
	}
}
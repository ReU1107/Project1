#pragma once
#include "../Math/Vector3.h"

namespace Engine
{
	namespace PhysicsSystem
	{
		// 線分
		struct LineSegment
		{
			Vector3 start;	// 開始位置
			Vector3 end;	// 終了位置

			float MinDistance(const Vector3& point) const;

		};

	}
}

#pragma once
#include "../Math/Vector3.h"
#include "../Math/Quaternion.h"

namespace Engine
{
	namespace PhysicsSystem
	{
		// Oriented Bounding Box
		struct OBB
		{
			Vector3 center;			// 中心座標
			Quaternion rotation;	// 回転
			Vector3 extents;		// 広がり
		};

	}
}
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
			Vector3 center;			// ���S���W
			Quaternion rotation;	// ��]
			Vector3 extents;		// �L����
		};

	}
}
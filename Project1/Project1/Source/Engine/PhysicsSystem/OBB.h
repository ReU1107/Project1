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
			Vector3 center;			// ’†SÀ•W
			Quaternion rotation;	// ‰ñ“]
			Vector3 extents;		// L‚ª‚è
		};

	}
}
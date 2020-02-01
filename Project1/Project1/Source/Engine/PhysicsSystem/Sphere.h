#pragma once
#include "../Math/Vector3.h"

namespace Engine
{

	namespace PhysicsSystem
	{
		struct Sphere
		{
			Vector3 center;
			float radius;

			Sphere()
				: center()
				, radius(0.0f)
			{
			}

			bool Contains(const Vector3& point) const;

		};
	}
}
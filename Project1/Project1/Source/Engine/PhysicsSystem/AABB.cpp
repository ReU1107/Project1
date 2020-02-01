#include "AABB.h"
#include "../Math/MathF.h"

namespace Engine
{
	namespace PhysicsSystem
	{
		bool AABB::Contains(const Vector3& point) const
		{
			if (min.x < point.x || max.x > point.x)
				return false;
			if (min.y < point.y || max.y > point.y)
				return false;
			if (min.z < point.z || max.z > point.z)
				return false;

			return true;
		}

		float AABB::MinDistance(const Vector3& point) const
		{
			/*
			—á:x‚Ì‚Ý
			point.x = 0.0f;
			min.x = 1.0f;
			max.x > min.x;
			(1.0f - 0.0f) > 0.0f;
			1.0f > 0.0f - 1.0f
			*/

			float dx = MathF::Max(min.x - point.x, 0.0f);
			dx = MathF::Max(dx, point.x - max.x);

			float dy = MathF::Max(min.y - point.y, 0.0f);
			dy = MathF::Max(dy, point.y - max.y);

			float dz = MathF::Max(min.z - point.z, 0.0f);
			dz = MathF::Max(dz, point.z - max.z);

			return 0.0f;
		}
	}
}
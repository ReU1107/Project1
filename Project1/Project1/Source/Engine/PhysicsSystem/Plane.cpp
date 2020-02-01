#include "Plane.h"

namespace Engine
{
	namespace PhysicsSystem
	{
		Plane::Plane(const Vector3& a, const Vector3& b, const Vector3& c)
			: normal(Vector3::Zero)
			, distance(0.0f)
		{
			Vector3 ab = b - a;
			Vector3 ac = c - a;
			normal = Vector3Normalize(Vector3Cross(ab, ac));

			distance = - Vector3Dot(a, normal);
		}

		float Plane::SignedDistance(const Vector3& point) const
		{
			return Vector3Dot(point, normal) - distance;
		}
	}

}

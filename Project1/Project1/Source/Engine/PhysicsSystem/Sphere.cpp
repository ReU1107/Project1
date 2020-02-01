#include "Sphere.h"
namespace Engine
{

	namespace PhysicsSystem
	{
		bool Sphere::Contains(const Vector3& point) const
		{
			float distance = (center - point).Length();
			
			return distance <= (radius * radius);
		}
	}
}
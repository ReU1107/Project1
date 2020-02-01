#include "SphereShape.h"

namespace Engine
{
	namespace PhysicsSystem
	{
		SphereShape::SphereShape()
			: base()
		{
		}

		SphereShape::~SphereShape()
		{
		}

		SphereShape::SphereShapePtr SphereShape::Create(float radius)
		{
			auto sphere = std::make_shared<SphereShape>();
			//sphere->m_shape = new btSphereShape(radius);
			return sphere;
		}
	}
}
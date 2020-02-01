#pragma once
#include "../Math/Vector3.h"

namespace Engine
{
	namespace PhysicsSystem
	{
		struct Plane
		{
			Vector3 normal;		// �@��
			float distance;		// 

			// �R���X�g���N�^
			Plane(const Vector3& a, const Vector3& b, const Vector3& c);

			float SignedDistance(const Vector3& point) const;

		};
	}
}
#pragma once
#include "../Math/Vector3.h"

namespace Engine
{
	namespace PhysicsSystem
	{
		// ����
		struct LineSegment
		{
			Vector3 start;	// �J�n�ʒu
			Vector3 end;	// �I���ʒu

			float MinDistance(const Vector3& point) const;

		};

	}
}

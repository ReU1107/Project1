#pragma once
#include "../Math/Vector3.h"
#include "../Math/Matrix4x4.h"
#include "../Math/Math.h"

namespace Engine
{
	namespace PhysicsSystem
	{
		// Axis Aligned Bounding Box
		struct AABB
		{
			Vector3 min;
			Vector3 max;

			// “à•ï‚·‚é‚©
			bool Contains(const Vector3& point) const;

			// Å¬‹——£
			float MinDistance(const Vector3& point) const;

			inline AABB operator*(const Matrix4x4& matrix) const
			{
				Vector3 vec1 = Vector3TransformCoord(this->min, matrix);
				Vector3 vec2 = Vector3TransformCoord(this->max, matrix);

				AABB result;
				if (vec1 < vec2)
				{
					result.min = vec1;
					result.max = vec2;
				}
				else
				{
					result.min = vec2;
					result.max = vec1;
				}

				return result;
			}

		};
	}
}
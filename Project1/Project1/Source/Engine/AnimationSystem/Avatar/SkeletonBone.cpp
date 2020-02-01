#include "SkeletonBone.h"

namespace Engine
{

	namespace AnimationSystem
	{
		SkeletonBone::SkeletonBone()
			: rotation(Vector4::Identity)
			, position(Vector3::Zero)
			, scale(1.0f, 1.0f, 1.0f)
		{
		}
	}
}
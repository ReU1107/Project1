#include "ChildMotion.h"
#include "Motion.h"

namespace Engine
{
	namespace AnimationSystem
	{
		ChildMotion::ChildMotion(std::shared_ptr<Motion> motion) noexcept
			: motion(motion)
		{
		}
	}
}


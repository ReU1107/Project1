#pragma once
#include <memory>

namespace Engine
{
	namespace AnimationSystem
	{
		class Motion;

		struct ChildMotion
		{
			std::shared_ptr<Motion> motion;
			float weight;
			ChildMotion(std::shared_ptr<Motion> motion) noexcept;
		};
	}
}

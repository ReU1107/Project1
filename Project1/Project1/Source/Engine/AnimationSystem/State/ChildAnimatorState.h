#pragma once
#include <memory>

namespace Engine
{
	namespace AnimationSystem
	{
		class AnimatorState;
		// サブステート
		struct ChildAnimatorState
		{
			std::shared_ptr<AnimatorState> state;
			ChildAnimatorState(std::shared_ptr<AnimatorState> state) noexcept;
		};
	}
}

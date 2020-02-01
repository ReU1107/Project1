#pragma once
#include <memory>

namespace Engine
{
	namespace AnimationSystem
	{

		class AnimatorStateMachine;
		// サブステートマシーン
		struct ChildAnimatorStateMachine
		{
			std::shared_ptr<AnimatorStateMachine> stateMachine;
			ChildAnimatorStateMachine(std::shared_ptr<AnimatorStateMachine> stateMachine) noexcept;
		};
	}
}
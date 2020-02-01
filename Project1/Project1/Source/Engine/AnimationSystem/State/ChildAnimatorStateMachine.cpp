#include "ChildAnimatorStateMachine.h"
#include "AnimatorStateMachine.h"

namespace Engine
{
	namespace AnimationSystem
	{
		ChildAnimatorStateMachine::ChildAnimatorStateMachine(std::shared_ptr<AnimatorStateMachine> stateMachine) noexcept
			: stateMachine(stateMachine)
		{
		}
	}
}

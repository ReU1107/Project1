#include "ChildAnimatorState.h"
#include "AnimatorState.h"

namespace Engine
{
	namespace AnimationSystem
	{

		ChildAnimatorState::ChildAnimatorState(std::shared_ptr<AnimatorState> state) noexcept
			: state(state)
		{
		}
	}
}
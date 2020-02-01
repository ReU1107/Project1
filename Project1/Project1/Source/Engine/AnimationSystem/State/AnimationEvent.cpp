#include "AnimationEvent.h"
namespace Engine
{
	namespace AnimationSystem
	{
		AnimationEvent::AnimationEvent() noexcept
			: m_state(nullptr)
		{
		}

		AnimationEvent::~AnimationEvent() noexcept
		{
		}

		void AnimationEvent::SetAnimationState(AnimationState* state)
		{
			m_state = state;
		}

		void AnimationEvent::Execute(float deltaTime)
		{
			m_process(deltaTime);
		}
	}
}
#pragma once
#include <memory>

namespace Engine
{
	namespace AnimationSystem
	{

		class AnimatorStateMachine;
		// �T�u�X�e�[�g�}�V�[��
		struct ChildAnimatorStateMachine
		{
			std::shared_ptr<AnimatorStateMachine> stateMachine;
			ChildAnimatorStateMachine(std::shared_ptr<AnimatorStateMachine> stateMachine) noexcept;
		};
	}
}
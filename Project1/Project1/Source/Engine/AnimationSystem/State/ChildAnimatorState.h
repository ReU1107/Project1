#pragma once
#include <memory>

namespace Engine
{
	namespace AnimationSystem
	{
		class AnimatorState;
		// �T�u�X�e�[�g
		struct ChildAnimatorState
		{
			std::shared_ptr<AnimatorState> state;
			ChildAnimatorState(std::shared_ptr<AnimatorState> state) noexcept;
		};
	}
}

#pragma once
#include <functional>

namespace Engine
{
	namespace AnimationSystem
	{
		// �O���錾
		class AnimationState;

		/*
		���������̕K�v����
		*/

		// �A�j���[�V�����C�x���g���N���X
		class AnimationEvent
		{
		private:
			using Process = std::function<void(float deltaTime)>;
		private:
			AnimationState* m_state;	// �֘A����A�j���[�V����
			Process m_process;
		public:
			// �R���X�g���N�^
			AnimationEvent() noexcept;
			// �f�X�g���N�^
			~AnimationEvent() noexcept;
		public:
			void SetAnimationState(AnimationState* state);

			// ���s
			void Execute(float deltaTime);
		};
	}
}
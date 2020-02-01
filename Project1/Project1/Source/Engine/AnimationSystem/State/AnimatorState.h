#pragma once
#include "../../Object.h"
#include <vector>
#include <memory>

namespace Engine
{
	namespace AnimationSystem
	{
		class Motion;
		class Avatar;
		class AvatarMask;
		class AnimatorStateTransition;
		class AnimatorStateMachine;

		class AnimatorState final : public std::enable_shared_from_this<AnimatorState>, public Object
		{
		private:
			using base = Object;
			using StateTransitionPtr = std::shared_ptr<AnimatorStateTransition>;
			using MotionPtr = std::shared_ptr<Motion>;
			using AvatarPtr = std::shared_ptr<Avatar>;
			using AvatarMaskPtr = std::shared_ptr<AvatarMask>;
			using StatePtr = std::shared_ptr<AnimatorState>;
			using StateMachinePtr = std::shared_ptr<AnimatorStateMachine>;
			using StateTransitions = std::vector<StateTransitionPtr>;

			enum class State : uint8_t
			{
				Stop,
				Play,
			};
		private:
			StateTransitions m_stateTransitions;		// �J�ڔz��
			MotionPtr m_motion;							// ���̃X�e�[�g�Ɋ���U��ꂽ���[�V����
			float m_cycleOffset;						// �I�t�Z�b�g
			float m_localTime;							// ���[�J������
			float m_speed;								// �Đ����x(�P��:�b)�f�t�H���g1.0s
			StateTransitionPtr m_currentTransition;		// 
			State m_state;								// ���
		public:
			// �R���X�g���N�^
			AnimatorState(const std::string& name);
			// �f�X�g���N�^
			virtual ~AnimatorState();

			static StatePtr Create(const std::string& name);
		public:
			// ���[�V�����ݒ�
			void SetMotion(MotionPtr motion);

			// �X�e�[�g�}�V�[���r�w�C�r�A�ǉ�
			template<class T>
			inline T* AddStateMachineBehaviour();

			// �J�ڐ�ǉ�
			StateTransitionPtr AddTransition(StatePtr destinationState);
			StateTransitionPtr AddTransition(StateMachinePtr destinationStateMachine);
			void AddTransition(StateTransitionPtr transition);

			StatePtr GetSaifityState();

			void Update(AvatarPtr avatar, AvatarMaskPtr mask, float deltaTime, float weight = 1.0f);

			// �X�s�[�h�ݒ�
			void SetSpeed(float speed = 1.0f);

			StateTransitionPtr GetCurrentTransition() const;

			// �Đ�
			void Play();
			// ���Z�b�g
			void Reset();
			// �X�g�b�v
			void Stop();

		};

		template<class T>
		inline T* AnimatorState::AddStateMachineBehaviour()
		{
			return nullptr;
		}
	}
}

using AnimatorStatePtr = std::shared_ptr<Engine::AnimationSystem::AnimatorState>;
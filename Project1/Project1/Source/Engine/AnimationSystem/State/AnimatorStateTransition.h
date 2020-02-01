#pragma once
#include "../../Object.h"
#include <vector>

namespace Engine
{
	namespace AnimationSystem
	{

		struct AnimatorCondition;
		class AnimatorState;
		class AnimatorStateMachine;
		class Avatar;
		class AvatarMask;

		// �A�j���[�V�����J�ڊ��N���X
		class AnimatorStateTransition : public Object
		{
		private:
			using base = Object;
			using AvatarPtr = std::shared_ptr<Avatar>;
			using AvatarMaskPtr = std::shared_ptr<AvatarMask>;
			using StatePtr = std::shared_ptr<AnimatorState>;
			using StateMachinePtr = std::shared_ptr<AnimatorStateMachine>;
			using Conditions = std::vector<AnimatorCondition>;

		private:
			Conditions m_conditions;			// �J�ڏ����z��
			StatePtr m_sourceState;				// �J�ڌ��̃X�e�[�g
			StatePtr m_destinationState;		// �J�ڐ�̃X�e�[�g
			StateMachinePtr m_stateMachine;		// 
			float m_transitionTime;				// ���b�����đJ�ڂ��邩
			float m_localTime;					// ���[�J���^�C��

		public:
			// �R���X�g���N�^
			AnimatorStateTransition() noexcept;
			// ���z�f�X�g���N�^
			virtual ~AnimatorStateTransition() noexcept;

		public:
			// �J�ڏ����ǉ�
			void AddCondition(const AnimatorCondition& condition);

			// �J�ڌ��̃X�e�[�g�ݒ�
			void SetSourceState(StatePtr state);

			// �J�ڐ�̃X�e�[�g�ݒ�
			void SetDestinationState(StatePtr state);

			// �J�ڐ�̃X�e�[�g�}�V�[���ݒ�
			void SetDestinationStateMachine(StateMachinePtr stateMachine);

			void SetTransitionTime(float transitionTime);

			// �J�ڐ�̃X�e�[�g�擾
			StatePtr GetDestinationState() const;

			// �J�ڐ�̃X�e�[�g�}�V�[���擾
			StateMachinePtr GetDestinationStateMachine() const;

			// �J�ڏ���
			bool Transition(AvatarPtr avatar, AvatarMaskPtr mask, float deltaTime, float weight = 1.0f);

			// ���Z�b�g����
			void Reset();

			// �����𖞂�����
			StatePtr GetSatisfyState();

		};
	}
}

using AnimatorStateTransitionPtr = std::shared_ptr<Engine::AnimationSystem::AnimatorStateTransition>;
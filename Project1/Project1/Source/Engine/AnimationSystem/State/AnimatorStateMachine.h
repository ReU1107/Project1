#pragma once
#include "../../Object.h"
#include <vector>
#include <memory>

/*
ChildAnimatorState,ChildAnimatorStateMachine
�����̂Ŏ�����
��2�̍\���͎̂Q�ƃJ�E���g��ύX���錠���͎����Ȃ�
���R:�R�s�[����������ɎQ�ƃJ�E���g�����x��
�ύX���Ă��܂��׎Q�ƃJ�E���g�̊Ǘ���AnimatorStateMachine������
*/

namespace Engine
{
	namespace AnimationSystem
	{
		class Avatar;
		class AvatarMask;
		class AnimatorState;
		struct ChildAnimatorState;
		struct ChildAnimatorStateMachine;
		class AnimatorStateTransition;
		class AnimatorControllerLayer;

		class AnimatorStateMachine final : public Object
		{
		private:
			using base = Object;
			using StateTransitionPtr = std::shared_ptr<AnimatorStateTransition>;
			using Transitions = std::vector<StateTransitionPtr>;
			using ChildStates = std::vector<ChildAnimatorState>;
			using ChildStateMachines = std::vector<ChildAnimatorStateMachine>;
			using AvatarPtr = std::shared_ptr<Avatar>;
			using AvatarMaskPtr = std::shared_ptr<AvatarMask>;
			using StatePtr = std::shared_ptr<AnimatorState>;
			using StateMachinePtr = std::shared_ptr<AnimatorStateMachine>;
			using ControllerLayerPtr = std::shared_ptr<AnimatorControllerLayer>;
		private:
			Transitions m_transitions;			// �S�ẴX�e�[�g�̑J�ڏ��
			ChildStates m_states;				// �X�e�[�g�z��
			ChildStateMachines m_stateMachines;	// �X�e�[�g�}�V�[���z��
			StatePtr m_defaultState;			// �f�t�H���g�̃X�e�[�g
			StatePtr m_currentState;			// ���ݍĐ����̃X�e�[�g
			ControllerLayerPtr m_owner;			// 
		public:
			// �R���X�g���N�^
			AnimatorStateMachine(const std::string& name) noexcept;
			// �f�X�g���N�^
			virtual ~AnimatorStateMachine() noexcept;

		public:
			void SetOwner(ControllerLayerPtr layer);

			// �X�e�[�g�ǉ�
			StatePtr AddState(const std::string& name);
			void AddState(StatePtr state);
			// �X�e�[�g�}�V�[���ǉ�
			StateMachinePtr AddStateMachine(const std::string& name);
			void AddStateMachine(StateMachinePtr stateMachine);

			// �X�e�[�g�擾
			StatePtr GetState(uint32_t index);
			StatePtr GetState(const std::string& name);
			// ���ݍĐ����̃X�e�[�g�擾
			StatePtr GetCurrentState() const;

		private:
			// Child������AnimatorState,AnimatorStateMachine���Đ�����
			StatePtr SubPlay(const std::string& stateName);
			StatePtr SubPlay(int32_t stateNameHash);

		public:
			// �Đ�
			bool Play(const std::string& stateName);
			bool Play(int32_t stateNameHash);

			void Update(AvatarPtr avatar, AvatarMaskPtr mask, float deltaTime);
			//// �Đ����Ă���A�j���[�V�������X�V
			//void Update();
			//// ���Z�b�g
			//void Reset();
			//// �X�g�b�v
			//void Stop();
		};
	}
}

using AnimatorStateMachinePtr = std::shared_ptr<Engine::AnimationSystem::AnimatorStateMachine>;
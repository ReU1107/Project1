#pragma once
#include <string>
#include <unordered_map>
#include <cstdint>
#include <memory>

/*
�����I�ȃA�j���[�V�����u�����f�B���O���s�������Ƃ���
Synced�֘A�̒l�����悤����
�u�����f�B���O�̎d���͉��Z�u�����f�B���O��
*/
/*
���C���[�����������Ƃ��Ă���I�u�W�F�N�g�̌^�������Ă���
���[�t�B���O�֘A�Ȃ�mesh���m�ɂ�SkinnedMeshRenderer
�X�L�j���O�֘A�Ȃ�Transform
*/

namespace Engine
{
	namespace AnimationSystem
	{
		class Motion;
		class AnimatorStateMachine;
		class AnimatorState;
		class AvatarMask;
		class Avatar;
		class AnimatorStateTransition;

		// ���C���[
		class AnimatorControllerLayer final
		{
		private:
			using AvatarPtr = std::shared_ptr<Avatar>;
			using MotionPtr = std::shared_ptr<Motion>;
			using AvatarMaskPtr = std::shared_ptr<AvatarMask>;
			using AnimatorStateTransitionPtr = std::shared_ptr<AnimatorStateTransition>;
			using AnimatorStatePtr = std::shared_ptr<AnimatorState>;
			using AnimatorStateMachinePtr = std::shared_ptr<AnimatorStateMachine>;
			using ControllerLayerPtr = std::shared_ptr<AnimatorControllerLayer>;
		private:
			std::string m_name;						// ���C���[��
			AnimatorStateMachinePtr m_stateMachine;	// �X�e�[�g�}�V�[��
			AvatarMaskPtr m_avatarMask;				// �A�o�^�[�}�X�N
			AnimatorStateTransitionPtr m_transition;// 
			int32_t m_syncedLayerIndex;				// �������郌�C���[�ԍ�
			float m_syncedWeight;					// �����̓x����

		public:
			// �R���X�g���N�^
			AnimatorControllerLayer(const std::string& name) noexcept;
			// �f�X�g���N�^
			~AnimatorControllerLayer() noexcept;

			static ControllerLayerPtr Create(const std::string& name);
			
		public:
			// �A�o�^�[�}�X�N�ݒ�
			void SetAvatarMask(AvatarMaskPtr avatarMask);
			// 
			void SetOverrideMotion(AnimatorStatePtr state, MotionPtr motion);

			void SetTransition(AnimatorStateTransitionPtr transition);

			// �X�e�[�g�}�V�[���擾
			AnimatorStateMachinePtr GetStateMachine() const;

			// �X�e�[�g�ǉ�
			void AddState(AnimatorStatePtr state);

			// �Đ�
			bool Play(const std::string& stateName);
			bool Play(int32_t stateNameHash);

			// ���C���[�X�V
			void Update(AvatarPtr avatar, float deltaTime);
		};
	}
}

using AnimatorControllerLayerPtr = std::shared_ptr<Engine::AnimationSystem::AnimatorControllerLayer>;
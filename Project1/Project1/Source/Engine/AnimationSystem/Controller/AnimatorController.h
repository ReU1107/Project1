#pragma once
#include <vector>
#include <memory>
#include "../../Object.h"

/*
���C���[�̕�����unity�Q��
��:
�g�̂𓮂����X�e�[�g�}�V�[���������Ă���Ȃ�
name Body; StateMachine�Ɂ��Ɍ������郂�[�V������ݒ�
��(���[�t�B���O��)�̃X�e�[�g�}�V�[��������Ȃ�
name Face; StateMachine�Ɂ��Ɍ������郂�[�V������ݒ�

*/
namespace Engine
{
	namespace AnimationSystem
	{
		class Motion;
		class Avatar;
		class AnimatorControllerParameter;

		// �O���錾
		class AnimatorControllerLayer;
		class AnimatorState;

		// �A�j���[�^�[����N���X
		class AnimatorController final : public Object
		{
		private:
			using base = Object;
			using LayerPtr = std::shared_ptr<AnimatorControllerLayer>;
			using Layers = std::vector<LayerPtr>;
			using ParameterPtr = std::shared_ptr<AnimatorControllerParameter>;
			using Parameters = std::vector<ParameterPtr>;
			using AnimatorStatePtr = std::shared_ptr<AnimatorState>;
			using MotionPtr = std::shared_ptr<Motion>;
			using AvatarPtr = std::shared_ptr<Avatar>;
			using RemoveIndices = std::vector<int32_t>;
			using AnimatorControllerPtr = std::shared_ptr<AnimatorController>;
		private:
			Layers m_layers;					// ���C���[�z��
			Parameters m_parameters;			// �p�����[�^�[�z��
			RemoveIndices m_layerIndices;		// ���C���[�z����ō폜�����ԍ����L��
			RemoveIndices m_parameterIndices;	// �p�����[�^�z����ō폜�����ԍ����L��

		public:
			// �R���X�g���N�^
			AnimatorController(const std::string& name) noexcept;
			// �f�X�g���N�^
			virtual ~AnimatorController() noexcept;

			static AnimatorControllerPtr Create(const std::string& name);

		public:
			// ���C���[�ǉ�
			LayerPtr AddLayer(const std::string& name);
			void AddLayer(LayerPtr layer);
			// �p�����[�^�ǉ�
			void AddParameter(ParameterPtr parameter);
			// 
			void MakeUniqueLayer(const std::string& name);
			// 
			void MakeUniqueParameter(const std::string& name);

			// ���[�V�����ǉ�
			AnimatorStatePtr AddMotion(MotionPtr motion);
			AnimatorStatePtr AddMotion(MotionPtr motion, int32_t layerIndex);

			// ���C���[�폜
			void RemoveLayer(int32_t index);
			void RemoveParameter(int32_t index);

			// ���C���[�擾
			LayerPtr GetLayer(int32_t index);

			// �X�V
			void Update(AvatarPtr avatar, float deltaTime);
		};
	}

}

using AnimatorControllerPtr = std::shared_ptr<Engine::AnimationSystem::AnimatorController>;
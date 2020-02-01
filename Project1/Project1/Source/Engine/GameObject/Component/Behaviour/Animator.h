#pragma once
#include "Behaviour.h"
#include "../../../Math/MathF.h"
#include <memory>
#include <vector>

namespace Engine
{
	namespace AnimationSystem
	{
		// �O���錾
		class Avatar;
		class Motion;
		class AnimatorController;
	}

	class Transform;

	// �A�j���[�^�[�N���X
	class Animator final : public Behaviour
	{
	private:
		using base = Behaviour;
		using TargetAvatar = std::shared_ptr<AnimationSystem::Avatar>;
		using ControllerPtr = std::shared_ptr<AnimationSystem::AnimatorController>;
		using AnimatorPtr = std::shared_ptr<Animator>;
	public:
		static std::vector<AnimatorPtr> allAnimators;
	private:
		TargetAvatar m_avatar;		// Animation��K�p����I�u�W�F�N�g
		ControllerPtr m_controller;	// �R���g���[���[
		bool m_isPlay;				// �Đ�����
	public:
		// �R���X�g���N�^
		Animator() noexcept;
		// �f�X�g���N�^
		virtual ~Animator() noexcept;
	public:
		// �C���X�^���XID
		static const InstanceID ID() { return InstanceID::Animator; }

		// �C���X�^���XID�擾
		virtual InstanceID GetInstanceID() const override { return InstanceID::Animator; }

	public:
		// �A�o�^�[�ݒ�
		void SetAvatar(TargetAvatar avatar);
		// �R���g���[���[�ݒ�
		void SetController(ControllerPtr controller);

		// �A�o�^�[�擾
		TargetAvatar GetAvatar() const;

		// �R���g���[���[�擾
		ControllerPtr GetController();

		// �Đ�
		void Play(const std::string& stateName, int32_t layerIndex = -1, float normalizedTime = MathF::NegativeInfinity);
		void Play(int32_t stateNameHash, int32_t layerIndex = -1, float normalizedTime = MathF::NegativeInfinity);

		bool IsPlay() const;

		// �A�j���[�V�����X�V
		void Update(float deltaTime);
	};


	template<>
	inline std::shared_ptr<Animator> Component::Create()
	{
		auto animator = std::make_shared<Animator>();

		Animator::allAnimators.push_back(animator);

		return animator;
	}

}
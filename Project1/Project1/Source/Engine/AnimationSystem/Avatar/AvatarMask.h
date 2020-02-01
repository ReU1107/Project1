#pragma once
#include "../../Object.h"
#include "../Enumerations/AvatarMaskBodyPart.h"

namespace Engine
{
	namespace AnimationSystem
	{
		class Avatar;

		class AvatarMask final : public Object
		{
		private:
			using base = Object;
			using AvatarPtr = std::shared_ptr<Avatar>;
		private:
			AvatarPtr m_baseAvatar;			// �}�X�N���悤�Ƃ��Ă���A�o�^�[
			uint32_t m_transformCount;		// �g�����X�t�H�[����
			AvatarMaskBodyPart m_maskPart;	// �}�X�N����p�[�c(�r�b�g���Z)
		public:
			// �R���X�g���N�^
			AvatarMask(const std::string& name) noexcept;
			// �f�X�g���N�^
			virtual ~AvatarMask() noexcept;
		public:
			// �A�o�^�[�ݒ�
			void SetAvatar(AvatarPtr avatar);

			// �}�X�N�p�[�c�ǉ�
			void AddMaskBodyPart(AvatarMaskBodyPart part);
			// �}�X�N����Ă���p�[�c�擾
			AvatarMaskBodyPart GetMaskBodyPart();

			// �A�o�^�[�{�[�����擾
			uint32_t GetTransformCount() const;

		};
	}
}

using AvatarMaskPtr = std::shared_ptr<Engine::AnimationSystem::AvatarMask>;
#pragma once
#include "../../Object.h"
#include "../Enumerations/HumanBodyBones.h"
#include <unordered_map>

namespace Engine
{
	namespace AnimationSystem
	{
		// �O���錾
		struct BodyPart;
		class Transform;

		class Avatar final : public Object
		{
		private:
			using base = Object;
			//using BodyParts = std::unordered_map<HumanBodyBones, BodyPart>;
			using BodyParts = std::unordered_map<std::string, BodyPart>;

		private:
			BodyParts m_bodyParts;	// �p�[�c�z��(�q���[�}�m�C�h)
			bool m_isHuman;			// �q���[�}��
		public:
			// �R���X�g���N�^
			Avatar() noexcept;
			// �f�X�g���N�^
			virtual ~Avatar() noexcept;
		public:
			// �g�����X�t�H�[�����擾
			uint32_t GetTransformCount() const;
			// �g�����X�t�H�[���擾
			//Transform * GetBoneTransform(HumanBodyBones humanBoneID) const;

			BodyPart GetBodyPart(const std::string& name);

			BodyParts& GetBodyParts();
		};
	}
}

using AvatarPtr = std::shared_ptr<Engine::AnimationSystem::Avatar>;
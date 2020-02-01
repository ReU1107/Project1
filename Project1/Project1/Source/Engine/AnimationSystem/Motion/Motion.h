#pragma once
#include "../../Utility/AccessObject.h"
#include <memory>

namespace Engine
{
	namespace AnimationSystem
	{
		// �O���錾
		class Avatar;
		class AvatarMask;

		// ���[�V�������N���X
		class Motion : public AccessObject<Motion>
		{
		private:
			using base = AccessObject<Motion>;
		protected:
			using AvatarPtr = std::shared_ptr<Avatar>;
			using AvatarMaskPtr = std::shared_ptr<AvatarMask>;
		public:
			// �R���X�g���N�^
			Motion(const std::string& name) noexcept;
			// �f�X�g���N�^
			virtual ~Motion() noexcept;
		public:
			// �C���X�^���XID
			static const InstanceID ID() { return InstanceID::Motion; }

			// �C���X�^���XID�擾
			virtual InstanceID GetInstanceID() const override { return InstanceID::Motion; }

		public:

			// �X�V
			virtual void Update(AvatarPtr avatar, AvatarMaskPtr mask, float deltaTime, float weight = 1.0f) = 0;

		};
	}
}
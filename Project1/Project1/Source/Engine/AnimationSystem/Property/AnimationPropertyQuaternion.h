#pragma once
#include "AnimationProperty.h"

namespace Engine
{
	namespace AnimationSystem
	{
		// �l�����v���p�e�B
		class AnimationPropertyQuaternion final : public AnimationProperty
		{
		private:
			using base = AnimationProperty;
			static constexpr uint32_t NumCurves = 4;
		public:
			// �R���X�g���N�^
			AnimationPropertyQuaternion() noexcept;
			// �f�X�g���N�^
			virtual ~AnimationPropertyQuaternion() noexcept;
		public:

			virtual void Update(AvatarPtr, AvatarMaskPtr mask, float time, float weight = 1.0f);

			virtual void Reset(AvatarPtr avatar, AvatarMaskPtr mask) override;

		};
	}
}
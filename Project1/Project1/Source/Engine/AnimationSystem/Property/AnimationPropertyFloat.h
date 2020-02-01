#pragma once
#include "AnimationProperty.h"

namespace Engine
{
	namespace AnimationSystem
	{
		class AnimationPropertyFloat final : public AnimationProperty
		{
		private:
			using base = AnimationProperty;
			static constexpr uint32_t NumCurves = 1;

		public:
			// �R���X�g���N�^
			AnimationPropertyFloat() noexcept;
			// �f�X�g���N�^
			virtual ~AnimationPropertyFloat() noexcept;
		public:
			virtual void Update(AvatarPtr avatar, AvatarMaskPtr mask, float time, float weight = 1.0f) override;

			virtual void Reset(AvatarPtr avatar, AvatarMaskPtr mask) override;

		};
	}
}
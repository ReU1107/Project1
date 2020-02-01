#pragma once
#include "AnimationProperty.h"

namespace Engine
{
	namespace AnimationSystem
	{
		class AnimationPropertyVector4 final : public AnimationProperty
		{
		private:
			using base = AnimationProperty;
			static constexpr uint32_t NumCurves = 4;

		public:
			// �R���X�g���N�^
			AnimationPropertyVector4() noexcept;
			// �f�X�g���N�^
			virtual ~AnimationPropertyVector4() noexcept;
		public:
			virtual void Update(AvatarPtr avatar, AvatarMaskPtr mask, float time, float weight = 1.0f) override;
		};
	}
}
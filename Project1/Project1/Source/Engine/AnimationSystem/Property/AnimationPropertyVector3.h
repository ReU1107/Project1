#pragma once
#include "AnimationProperty.h"

namespace Engine
{
	namespace AnimationSystem
	{
		class AnimationPropertyVector3 final : public AnimationProperty
		{
		private:
			using base = AnimationProperty;
			static constexpr uint32_t NumCurves = 3;

		public:
			// コンストラクタ
			AnimationPropertyVector3() noexcept;
			// デストラクタ
			virtual ~AnimationPropertyVector3() noexcept;

		public:
			virtual void Update(AvatarPtr avatar, AvatarMaskPtr mask, float time, float weight = 1.0f) override;

			virtual void Reset(AvatarPtr avatar, AvatarMaskPtr mask) override;

		};
	}
}
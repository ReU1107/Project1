#pragma once
#include "AnimationProperty.h"

namespace Engine
{
	namespace AnimationSystem
	{
		class AnimationPropertyVector2 final : public AnimationProperty
		{
		private:
			using base = AnimationProperty;
			static constexpr uint32_t NumCurves = 2;

		public:
			// コンストラクタ
			AnimationPropertyVector2() noexcept;
			// デストラクタ
			virtual ~AnimationPropertyVector2() noexcept;
		public:
			virtual void Update(AvatarPtr avatar, AvatarMaskPtr mask, float time, float weight = 1.0f) override;
		};
	}
}
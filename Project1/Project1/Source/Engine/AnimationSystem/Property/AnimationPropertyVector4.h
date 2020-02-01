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
			// コンストラクタ
			AnimationPropertyVector4() noexcept;
			// デストラクタ
			virtual ~AnimationPropertyVector4() noexcept;
		public:
			virtual void Update(AvatarPtr avatar, AvatarMaskPtr mask, float time, float weight = 1.0f) override;
		};
	}
}
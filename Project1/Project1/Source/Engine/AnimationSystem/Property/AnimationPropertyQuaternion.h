#pragma once
#include "AnimationProperty.h"

namespace Engine
{
	namespace AnimationSystem
	{
		// 四元数プロパティ
		class AnimationPropertyQuaternion final : public AnimationProperty
		{
		private:
			using base = AnimationProperty;
			static constexpr uint32_t NumCurves = 4;
		public:
			// コンストラクタ
			AnimationPropertyQuaternion() noexcept;
			// デストラクタ
			virtual ~AnimationPropertyQuaternion() noexcept;
		public:

			virtual void Update(AvatarPtr, AvatarMaskPtr mask, float time, float weight = 1.0f);

			virtual void Reset(AvatarPtr avatar, AvatarMaskPtr mask) override;

		};
	}
}
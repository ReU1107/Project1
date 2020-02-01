#pragma once
#include "AnimationProperty.h"

namespace Engine
{
	namespace AnimationSystem
	{
		// 色情報をアニメーションする際に使用
		class AnimationPropertyColor4 final : public AnimationProperty
		{
		private:
			using base = AnimationProperty;
		public:
			// コンストラクタ
			AnimationPropertyColor4() noexcept;
			// デストラクタ
			virtual ~AnimationPropertyColor4() noexcept;
		public:
			virtual void Update(float frame);
		};

	}
}
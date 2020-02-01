#pragma once
#include "AnimationProperty.h"

namespace Engine
{
	namespace AnimationSystem
	{
		/*
		8bit* 4
		*/

		// 色情報をアニメーションする際に使用
		class AnimationPropertyColor32 final : public AnimationProperty
		{
		private:
			using base = AnimationProperty;
		public:
			// コンストラクタ
			AnimationPropertyColor32() noexcept;
			// デストラクタ
			virtual ~AnimationPropertyColor32() noexcept;
		public:
			virtual void Update(float frame);
		};
	}
}